using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameWebSite.Models
{
    public class Introducao
    {
        public int ID { get; set; }
        public string remetenteID { get; set; }
        public string intermediarioID { get; set; }
        public string destinatarioID { get; set; }
        public string estado { get; set; }
    }
}