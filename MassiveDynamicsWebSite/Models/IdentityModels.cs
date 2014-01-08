using Microsoft.AspNet.Identity.EntityFramework;
using Microsoft.AspNet.Identity;
using System.ComponentModel.DataAnnotations;
using System.Collections.Generic;
using SocialGameWebSite.Models;

namespace MassiveDynamicsWebSite.Models
{
    public class ApplicationUser : IdentityUser
    {
        [Required]
        public string FirstName { get; set; }

        [Required]
        public string LastName { get; set; }

        [Required]
        public string Email { get; set; }


        [DisplayFormat(DataFormatString = "{0:dd MMM yyyy}")]
        public System.DateTime Date { get; set; }
        /*public virtual Humor humor { get; set; }
        public int humorID { get; set; }*/
        public string perfilfacebook { get; set; }
        public string perfillinkedin { get; set; }
    }


    public class ApplicationDbContext : IdentityDbContext<ApplicationUser>
    {
        public ApplicationDbContext()
            : base("DefaultConnection")
        {

        }

        public System.Data.Entity.DbSet<SocialGameWebSite.Models.Jogo> Jogo { get; set; }

        public System.Data.Entity.DbSet<SocialGameWebSite.Models.EstadoRelacao> EstadoRelacao { get; set; }

        public System.Data.Entity.DbSet<SocialGameWebSite.Models.Relacao> Relacao { get; set; }

        public System.Data.Entity.DbSet<SocialGameWebSite.Models.Introducao> Introducao { get; set; }

        public System.Data.Entity.DbSet<SocialGameWebSite.Models.Humor> Humor { get; set; }

        public System.Data.Entity.DbSet<SocialGameWebSite.Models.Tag> Tag { get; set; }
    }


    public class IdentityManager
    {
        public bool RoleExists(string name)
        {
            var rm = new RoleManager<IdentityRole>(
                new RoleStore<IdentityRole>(new ApplicationDbContext()));
            return rm.RoleExists(name);
        }


        public bool CreateRole(string name)
        {
            var rm = new RoleManager<IdentityRole>(
                new RoleStore<IdentityRole>(new ApplicationDbContext()));
            var idResult = rm.Create(new IdentityRole(name));
            return idResult.Succeeded;
        }


        public bool CreateUser(ApplicationUser user, string password)
        {
            var um = new UserManager<ApplicationUser>(
                new UserStore<ApplicationUser>(new ApplicationDbContext()));
            var idResult = um.Create(user, password);
            return idResult.Succeeded;
        }


        public bool AddUserToRole(string userId, string roleName)
        {
            var um = new UserManager<ApplicationUser>(
                new UserStore<ApplicationUser>(new ApplicationDbContext()));
            var idResult = um.AddToRole(userId, roleName);
            return idResult.Succeeded;
        }


        public void ClearUserRoles(string userId)
        {
            var um = new UserManager<ApplicationUser>(
                new UserStore<ApplicationUser>(new ApplicationDbContext()));
            var user = um.FindById(userId);
            var currentRoles = new List<IdentityUserRole>();
            currentRoles.AddRange(user.Roles);
            foreach (var role in currentRoles)
            {
                um.RemoveFromRole(userId, role.Role.Name);
            }
        }
    }
}