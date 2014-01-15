#!/usr/bin/perl -w

##################################
#
# check_snmp_ifstatus.pl
#
# Based on check_iftraffic.pl
#
# Use SNMP to get the current UP/DOWN status, max bandwidth, and current
# bandwidth usage of a given interface. Uses a /tmp file to store the data
# from the last check in order to calculate usage stats.
#
# Note: 32bit counters are used. A Gigabit interface operating at full speed
#       will cause a counter overflow in 34 seconds. Therefore it is 
#       recommended to use a polling rate of 30 seconds or less on
#       GBit interfaces with heavy traffic to ensure accuracy. A 100Mb 
#       interface would take over 5 minutes to overflow the counter.
#
##################################

use strict;

use Net::SNMP;
use Getopt::Long;
&Getopt::Long::config('bundling');

use Data::Dumper;

my $host_address;
my $if_number;
my $if_descr;
my $if_speed = 0;
my $opt_h;
my $units;
my $max_value;
my $max_if_speed;
my $admin_status;
my $oper_status;
my $in_bytes;
my $out_bytes;

my $warn_pct = 85;
my $crit_pct = 98;

my $session;
my $error;
my $port = 161;
my $snmp_version = 1;
my $community = "public";

my $update_time = time;
my $max_counter32 = 2 ** 32;

my @snmpoids;

# SNMP OIDs for network traffic
my $snmpIfDescr       = '1.3.6.1.2.1.2.2.1.2';
my $snmpIfSpeed       = '1.3.6.1.2.1.2.2.1.5';
my $snmpIfAdminStatus = '1.3.6.1.2.1.2.2.1.7';
my $snmpIfOperStatus  = '1.3.6.1.2.1.2.2.1.8';
my $snmpIfInOctets    = '1.3.6.1.2.1.2.2.1.10';
my $snmpIfOutOctets   = '1.3.6.1.2.1.2.2.1.16';
my $response;

# Path to tmp files
my $TRAFFIC_FILE = "/tmp/iftraffic";

my %STATUS_CODE =
  ( 'OK' => '0', 'WARNING' => '1', 'CRITICAL' => '2', 'UNKNOWN' => '3' );

my $status = GetOptions(
  "h|help"        => \$opt_h,
  "C|community=s" => \$community,
  "v|version=i"   => \$snmp_version,
  "w|warning=s"   => \$warn_pct,
  "c|critical=s"  => \$crit_pct,
  "b|bandwidth=i" => \$if_speed,
  "p|port=i"      => \$port,
  "i|interface=s" => \$if_descr,
  "H|hostname=s"  => \$host_address
  );

if ( ( $status == 0 ) or ( !$host_address ) or ( !$if_descr ) ) {
  print_usage();
  exit $STATUS_CODE{'UNKNOWN'};
}

if ( $snmp_version =~ /[12]/ ) {
  ( $session, $error ) = Net::SNMP->session(
    -hostname  => $host_address,
    -community => $community,
    -port      => $port,
    -version   => $snmp_version
    );
  if ( !defined($session) ) {
    print("UNKNOWN: $error");
    exit $STATUS_CODE{'UNKNOWN'};
  }
}
else {
  print("UNKNOWN: No support for SNMP v$snmp_version \n");
  exit $STATUS_CODE{'UNKNOWN'};
}

$if_number = fetch_ifdescr( $session, $if_descr );

push( @snmpoids, $snmpIfSpeed . "." . $if_number );
push( @snmpoids, $snmpIfAdminStatus . "." . $if_number );
push( @snmpoids, $snmpIfOperStatus . "." . $if_number );
push( @snmpoids, $snmpIfInOctets . "." . $if_number );
push( @snmpoids, $snmpIfOutOctets . "." . $if_number );

if ( !defined( $response = $session->get_request(@snmpoids) ) ) {
  my $answer = $session->error;
  $session->close;
  print("WARNING: SNMP error: $answer\n");
  exit $STATUS_CODE{'WARNING'};
}

$max_if_speed = $response->{ $snmpIfSpeed       . "." . $if_number };
$admin_status = $response->{ $snmpIfAdminStatus . "." . $if_number };
$oper_status  = $response->{ $snmpIfOperStatus  . "." . $if_number };
$in_bytes     = $response->{ $snmpIfInOctets    . "." . $if_number };
$out_bytes    = $response->{ $snmpIfOutOctets   . "." . $if_number };

$session->close;

if ( $if_speed == 0 ) {
  $if_speed = $max_if_speed;
}

my $row;
my $old_update_time = $update_time - 1;
my $old_in_bytes = $in_bytes;
my $old_out_bytes = $out_bytes;

if ( open( FILE, "<" . $TRAFFIC_FILE . "_if" . $if_number . "_" . $host_address ) ) {
  while ( $row = <FILE> ) {
    chomp($row);
    ( $old_update_time, $old_in_bytes, $old_out_bytes ) = split( ":", $row );
  }
  close(FILE);
}

open( FILE, ">" . $TRAFFIC_FILE . "_if" . $if_number . "_" . $host_address )
  or die "\nCan't open $TRAFFIC_FILE for writing: $!";
printf FILE ( "%s:%.0lu:%.0lu\n", $update_time, $in_bytes, $out_bytes );
close(FILE);

my $time_diff = $update_time - $old_update_time;
if ( $time_diff < 1 ) { 
  $time_diff = $update_time;
  $old_in_bytes = 0;
x
  $old_out_bytes = 0;
}

$in_bytes  = adjust_overflow( $in_bytes,  $old_in_bytes,  $max_counter32 );
$out_bytes = adjust_overflow( $out_bytes, $old_out_bytes, $max_counter32 );

my $RXbps = int( ( ( $in_bytes - $old_in_bytes ) / $time_diff ) * 8 );
my $TXbps = int( ( ( $out_bytes - $old_out_bytes ) / $time_diff ) * 8 );

my $RXpct = int($RXbps / $if_speed * 10000) / 100;
my $TXpct = int($TXbps / $if_speed * 10000) / 100;

my $RXunits = convert_units($RXbps);
my $TXunits = convert_units($TXbps);
my $IFunits = convert_units($if_speed);

my $warn_bps = $if_speed * $warn_pct / 100;
my $crit_bps = $if_speed * $crit_pct / 100;

my $warn_overflow = int($max_counter32 / ( $if_speed / 8 ));

my $perfdata = "\|RXbps=$RXbps;$warn_bps;$crit_bps;0;$if_speed TXbps=$TXbps;$warn_bps;$crit_bps;0;$if_speed RXpct=$RXpct%;$warn_pct;$crit_pct;0;100 TXpct=$TXpct%;$warn_pct;$crit_pct;0;100 elapsed=$time_diff" . "s;$warn_overflow;;;";

if ( $admin_status == 0 ) {
  print("CRITICAL: $if_descr is administratively DOWN" . $perfdata);
  exit $STATUS_CODE{'CRITICAL'};
}
elsif ( $oper_status == 0 ) {
  print("CRITICAL: $if_descr is physically DOWN" . $perfdata);
  exit $STATUS_CODE{'CRITICAL'};
}
elsif (( $RXbps >= $crit_bps ) or ( $TXbps >= $crit_bps ) ) {
  print("CRITICAL: $if_descr is UP at $IFunits. RX=$RXunits ($RXpct%), TX=$TXunits ($TXpct%)" . $perfdata);
  exit $STATUS_CODE{'CRITICAL'};
}
elsif (( $RXbps >= $warn_bps ) or ( $TXbps >= $warn_bps ) ) {
  print("WARNING: $if_descr is UP at $IFunits. RX=$RXunits ($RXpct%), TX=$TXunits ($TXpct%)" . $perfdata);
  exit $STATUS_CODE{'WARNING'};
}
elsif ( $time_diff >= $warn_overflow ) {
  print("WARNING: Sample Rate too slow. Possible counter overflows. $if_descr is UP at $IFunits. RX=$RXunits ($RXpct%), TX=$TXunits ($TXpct%)" . $perfdata);
  exit $STATUS_CODE{'WARNING'};
}
else {
  print("OK: $if_descr is UP at $IFunits. RX=$RXunits ($RXpct%), TX=$TXunits ($TXpct%)" . $perfdata);
  exit $STATUS_CODE{'OK'};
}

exit $STATUS_CODE{'UNKNOWN'};

##################################
#
# Subroutines
#
##################################

sub print_usage {
        print <<EOU;

    Usage: check_snmp_ifstatus.pl -H hostaddress -i "if_description" [-b if_max_bps] [-C snmp_community] [-v 1|2] [-p snmp_port] [-w warn] [-c crit]

    Options:
    -H --host STRING or IPADDRESS
        IP Address of host to check. Required.
    -i --interface STRING
        Full name of the interface to check. Required.
        Examples would be eth0 or FastEthernet0/1
    -C --community STRING
        SNMP Community string. Optional. Defaults to 'public'
    -v --version INTEGER
        SNMP Version ( 1 or 2 ). Optional. Defaults to 1
    -p --port INTEGER
        SNMP port. Optional. Defaults to 161
    -b --bandwidth INTEGER
        Interface maximum speed in bits per second. Optional.
        Use this to override the value returned by SNMP if it lies about 
        the max speed of the interface.
    -w --warning INTEGER
        % of bandwidth usage necessary to result in warning status. Optional.
        Defaults to $warn_pct%
    -c --critical INTEGER
        % of bandwidth usage necessary to result in critical status. Optional.
        Defaults to $crit_pct%

EOU

        exit( $STATUS_CODE{"UNKNOWN"} );
}

sub fetch_ifdescr {
  my $state;
  my $response;
  my $snmpkey;
  my $answer;
  my $key;

  my ( $session, $ifdescr ) = @_;

  if ( !defined( $response = $session->get_table($snmpIfDescr) ) ) {
    $answer = $session->error;
    $session->close;
    $state = 'CRITICAL';
    $session->close;
    exit $STATUS_CODE{$state};
  }

  foreach $key ( keys %{$response} ) {
    if ( $response->{$key} =~ /^$ifdescr$/ ) {
      $key =~ /.*\.(\d+)$/;
      $snmpkey = $1;
    }
  }
  unless ( defined $snmpkey ) {
    $session->close;
    $state = 'CRITICAL';
    printf "$state: Could not match $ifdescr \n";
    exit $STATUS_CODE{$state};
  }
  return $snmpkey;
}

# Test and adjust for a 32 bit counter overflow
sub adjust_overflow {
  my ( $test_num, $last_num, $max_counter ) = @_;
  $test_num += $max_counter if ( $test_num < $last_num );
  return $test_num;
}

# Convert bps to G/M/Kbps
sub convert_units {
  my ( $base ) = @_;
  my $unit = "bps";
  if ($base >= 1000) {
    $base = $base / 1000;
    $unit = "Kbps"
  }
  if ($base >= 1000) {
    $base = $base / 1000;
    $unit = "Mbps"
  }
  if ($base >= 1000) {
    $base = $base / 1000;
    $unit = "Gbps"
  }
  $base = sprintf( "%.4g", $base) . $unit;
  return $base;
}
