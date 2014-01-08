namespace MassiveDynamicsWebSite.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class jogomig : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Jogoes",
                c => new
                    {
                        ID = c.Int(nullable: false, identity: true),
                        nome = c.String(),
                    })
                .PrimaryKey(t => t.ID);
            
        }
        
        public override void Down()
        {
            DropTable("dbo.Jogoes");
        }
    }
}
