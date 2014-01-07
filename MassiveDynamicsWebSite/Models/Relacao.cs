using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameWebSite.Models
{
    public class Relacao
    {
        public int ID { get; set; }
        public virtual EstadoRelacao estadorelacao{ get; set; }
        public int estadorelacaoID { get; set; }
        public string user1ID { get; set; }
        public string user2ID { get; set; }
        public int peso { get; set; }
        public ICollection<Tag> tags { get; set; }
    }
}