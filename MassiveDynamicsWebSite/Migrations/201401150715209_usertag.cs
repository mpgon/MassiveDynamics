namespace MassiveDynamicsWebSite.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class usertag : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.ApplicationUserTags",
                c => new
                    {
                        ApplicationUser_Id = c.String(nullable: false, maxLength: 128),
                        Tag_ID = c.Int(nullable: false),
                    })
                .PrimaryKey(t => new { t.ApplicationUser_Id, t.Tag_ID })
                .ForeignKey("dbo.AspNetUsers", t => t.ApplicationUser_Id, cascadeDelete: true)
                .ForeignKey("dbo.Tags", t => t.Tag_ID, cascadeDelete: true)
                .Index(t => t.ApplicationUser_Id)
                .Index(t => t.Tag_ID);
            
        }
        
        public override void Down()
        {
            DropForeignKey("dbo.ApplicationUserTags", "Tag_ID", "dbo.Tags");
            DropForeignKey("dbo.ApplicationUserTags", "ApplicationUser_Id", "dbo.AspNetUsers");
            DropIndex("dbo.ApplicationUserTags", new[] { "Tag_ID" });
            DropIndex("dbo.ApplicationUserTags", new[] { "ApplicationUser_Id" });
            DropTable("dbo.ApplicationUserTags");
        }
    }
}
