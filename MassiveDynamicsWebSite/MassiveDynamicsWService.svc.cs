using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using MassiveDynamicsWebSite.Models;
using MassiveDynamicsWebSite.Controllers;

namespace SocialGameWebSite
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "MassiveDynamicsWService" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select MassiveDynamicsWService.svc or MassiveDynamicsWService.svc.cs at the Solution Explorer and start debugging.
    public class MassiveDynamicsWService : IMassiveDynamicsWService
    {
        bool loginRes = false;

        public bool authenticate(string user, string pass)
        {
            loginInDb(user, pass);
            return loginRes;
        }


        public async void loginInDb(string user, string pass)
        {
            AccountController ac = new AccountController();
            var u = await ac.UserManager.FindAsync(user, pass);
            if (u != null)
            {
                loginRes = true;
            }
        }

        public string getUsers()
        {
            string res = "";

            ApplicationDbContext db = new ApplicationDbContext();
            var users = db.Users.ToList();
            res+=users.Count()+";";
            foreach(ApplicationUser user in users){
                res += user.UserName + ";" + user.humor.nome + ";";
                /*int numTags = 2; //user.tags.Count();
                res += numTags+";";*/
            }

            return res;
        }

        public string getRelacoes()
        {
            ApplicationDbContext db = new ApplicationDbContext();
            int i = 0;
            string res= "";
            foreach(Models.Relacao rel in db.Relacao.ToList()){
                string username1 = db.Database.SqlQuery<string>("SELECT [UserName] from [ARQSI042].[dbo].[AspNetUsers] WHERE [Id] = '" + rel.user1ID + "'").FirstOrDefault<string>(); ;
                string username2 = db.Database.SqlQuery<string>("SELECT [UserName] from [ARQSI042].[dbo].[AspNetUsers] WHERE [Id] = '" + rel.user2ID + "'").FirstOrDefault<string>(); ;
                res += username1 + ";" + username2 + ";";
            }
            return res;
        }
    }
}
