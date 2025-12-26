using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System;
using System.Globalization;

namespace SeminarC_
{
    public class MessageTask : Task
    {
        private string mesaj;
        private string from;
        private string to;
        private DateTime date;
        public MessageTask(string taskID, string descriere, string mesaj, string from, string to, DateTime date)
            : base(taskID, descriere)
        {
            this.mesaj = mesaj;
            this.from = from;
            this.to = to;
            this.date = date;
        }
        public string Mesaj
        {
            get { return mesaj; }
            set { mesaj = value; }
        }
        public string From
        {
            get { return from; }
            set { from = value; }
        }
        public string To
        {
            get { return to; }
            set { to = value; }
        }
        public DateTime Date
        {
            get { return date; }
            set { date = value; }
        }
        public override void Execute()
        {
            string formattedDate = date.ToString("yyyy-MM-dd HH:mm:ss", CultureInfo.InvariantCulture);
            Console.WriteLine($"Mesaj: {mesaj}");
            Console.WriteLine($"Creat la: {formattedDate}");
        }
        public override string ToString()
        {
            return base.ToString() + $"| message: {mesaj}| from: {from}| to: {to}| date: {Date.ToString("yyyy-MM-dd HH:mm:ss")}";
        }
    }

}