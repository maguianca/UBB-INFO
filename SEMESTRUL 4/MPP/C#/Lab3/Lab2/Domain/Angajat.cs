using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2.Domain
{
    internal class Angajat : Entity<int>
    {
        private String username;
        private String password;
        private String nume;

        public Angajat(string username, string password, string nume)
        {
            this.username = username;
            this.password = password;
            this.nume = nume;
        }
        public string Username
        {
            get { return this.username; }
            set { this.username = value; }
        }
        public string Password
        {
            get { return this.password; }
            set { this.password = value; }
        }
        public string Nume
        {
            get { return this.nume; }
            set { this.nume = value; }
        }
        public override string ToString()
        {
            return $"Nume: {this.nume}, Username: {this.username}, Parola: {this.password}";
        }
    }
}
