namespace MassiveDynamicsWebSite.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class prevExtendAccountMig : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.EstadoRelacaos",
                c => new
                    {
                        ID = c.Int(nullable: false, identity: true),
                        jogoID = c.Int(nullable: false),
                        estado = c.String(),
                    })
                .PrimaryKey(t => t.ID)
                .ForeignKey("dbo.Jogoes", t => t.jogoID, cascadeDelete: true)
                .Index(t => t.jogoID);
            
            CreateTable(
                "dbo.Humors",
                c => new
                    {
                        ID = c.Int(nullable: false, identity: true),
                        nome = c.String(),
                    })
                .PrimaryKey(t => t.ID);
            
            CreateTable(
                "dbo.Introducaos",
                c => new
                    {
                        ID = c.Int(nullable: false, identity: true),
                        remetenteID = c.String(),
                        intermediarioID = c.String(),
                        destinatarioID = c.String(),
                        estado = c.String(),
                    })
                .PrimaryKey(t => t.ID);
            
            CreateTable(
                "dbo.Relacaos",
                c => new
                    {
                        ID = c.Int(nullable: false, identity: true),
                        estadorelacaoID = c.Int(nullable: false),
                        user1ID = c.String(),
                        user2ID = c.String(),
                        peso = c.Int(nullable: false),
                    })
                .PrimaryKey(t => t.ID)
                .ForeignKey("dbo.EstadoRelacaos", t => t.estadorelacaoID, cascadeDelete: true)
                .Index(t => t.estadorelacaoID);
            
            CreateTable(
                "dbo.Tags",
                c => new
                    {
                        ID = c.Int(nullable: false, identity: true),
                        nome = c.String(),
                        tipo = c.String(),
                    })
                .PrimaryKey(t => t.ID);
            
            CreateTable(
                "dbo.TagRelacaos",
                c => new
                    {
                        Tag_ID = c.Int(nullable: false),
                        Relacao_ID = c.Int(nullable: false),
                    })
                .PrimaryKey(t => new { t.Tag_ID, t.Relacao_ID })
                .ForeignKey("dbo.Tags", t => t.Tag_ID, cascadeDelete: true)
                .ForeignKey("dbo.Relacaos", t => t.Relacao_ID, cascadeDelete: true)
                .Index(t => t.Tag_ID)
                .Index(t => t.Relacao_ID);
            
        }
        
        public override void Down()
        {
            DropForeignKey("dbo.TagRelacaos", "Relacao_ID", "dbo.Relacaos");
            DropForeignKey("dbo.TagRelacaos", "Tag_ID", "dbo.Tags");
            DropForeignKey("dbo.Relacaos", "estadorelacaoID", "dbo.EstadoRelacaos");
            DropForeignKey("dbo.EstadoRelacaos", "jogoID", "dbo.Jogoes");
            DropIndex("dbo.TagRelacaos", new[] { "Relacao_ID" });
            DropIndex("dbo.TagRelacaos", new[] { "Tag_ID" });
            DropIndex("dbo.Relacaos", new[] { "estadorelacaoID" });
            DropIndex("dbo.EstadoRelacaos", new[] { "jogoID" });
            DropTable("dbo.TagRelacaos");
            DropTable("dbo.Tags");
            DropTable("dbo.Relacaos");
            DropTable("dbo.Introducaos");
            DropTable("dbo.Humors");
            DropTable("dbo.EstadoRelacaos");
        }
    }
}
