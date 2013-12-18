using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(MassiveDynamicsWebSite.Startup))]
namespace MassiveDynamicsWebSite
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            ConfigureAuth(app);
        }
    }
}
