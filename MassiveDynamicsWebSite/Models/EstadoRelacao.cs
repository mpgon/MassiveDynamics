using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameWebSite.Models
{
    public class EstadoRelacao
    {
        public int ID { get; set; }
        public virtual Jogo jogo { get; set; }
        public int jogoID { get; set; }
        public string estado { get; set; }
    }
}