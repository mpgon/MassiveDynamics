using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameWebSite.Models
{
    public class Tag
    {
        public int ID { get; set; }
        public string nome { get; set; }
        public string tipo { get; set; }
        public ICollection<Relacao> relacoes { get; set; }
        public ICollection<string> users { get; set; }
    }
}