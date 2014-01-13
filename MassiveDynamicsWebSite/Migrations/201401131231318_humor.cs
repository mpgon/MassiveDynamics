namespace MassiveDynamicsWebSite.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class humor : DbMigration
    {
        public override void Up()
        {
            AddColumn("dbo.AspNetUsers", "humorID", c => c.Int());
            CreateIndex("dbo.AspNetUsers", "humorID");
            AddForeignKey("dbo.AspNetUsers", "humorID", "dbo.Humors", "ID", cascadeDelete: true);
        }
        
        public override void Down()
        {
            DropForeignKey("dbo.AspNetUsers", "humorID", "dbo.Humors");
            DropIndex("dbo.AspNetUsers", new[] { "humorID" });
            DropColumn("dbo.AspNetUsers", "humorID");
        }
    }
}
