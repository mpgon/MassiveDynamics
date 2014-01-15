using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace SocialGameWebSite
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IMassiveDynamicsWService" in both code and config file together.
    [ServiceContract]
    public interface IMassiveDynamicsWService
    {

        [OperationContract]
        bool authenticate(string user, string pass);

        void loginInDb(string user, string pass);

        [OperationContract]
        string getUsers();
        [OperationContract]
        string getRelacoes();
    }
}
