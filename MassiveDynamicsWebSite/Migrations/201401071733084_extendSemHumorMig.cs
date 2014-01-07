namespace MassiveDynamicsWebSite.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class extendSemHumorMig : DbMigration
    {
        public override void Up()
        {
            AddColumn("dbo.AspNetUsers", "Date", c => c.DateTime());
            AddColumn("dbo.AspNetUsers", "perfilfacebook", c => c.String());
            AddColumn("dbo.AspNetUsers", "perfillinkedin", c => c.String());
        }
        
        public override void Down()
        {
            DropColumn("dbo.AspNetUsers", "perfillinkedin");
            DropColumn("dbo.AspNetUsers", "perfilfacebook");
            DropColumn("dbo.AspNetUsers", "Date");
        }
    }
}
