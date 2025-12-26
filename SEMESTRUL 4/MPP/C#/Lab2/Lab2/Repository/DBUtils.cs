using System;
using System.Data;
using System.Collections.Generic;
using System.Data.SQLite;
using Lab2.Repository;
namespace Lab2.Repository
{
	public static class DBUtils
	{
		

		private static IDbConnection instance = null;

        public static IDbConnection GetConnection(IDictionary<string, string> props)
        {
            if (instance == null || instance.State == ConnectionState.Closed)
            {
                instance = getNewConnection(props);
                instance.Open();
            }
            return instance;
        }

        private static IDbConnection getNewConnection(IDictionary<string,string> props)
		{
			
			return ConnectionUtils.ConnectionFactory.getInstance().createConnection(props);


		}
	}
}
