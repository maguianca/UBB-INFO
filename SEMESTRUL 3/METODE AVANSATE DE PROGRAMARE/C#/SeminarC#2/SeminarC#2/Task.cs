using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeminarC_
{
    public abstract class Task
    {
        private string taskID;
        private string descriere;
        public Task(string taskID, string descriere)
        {
            this.taskID = taskID;
            this.descriere = descriere;
        }
        public string TaskID
        {
            get { return taskID; }
            set { taskID = value; }
        }

        public string Descriere
        {
            get { return descriere; }
            set { descriere = value; }
        }
        public abstract void Execute();
        public override string ToString()
        {
            return $"id: {taskID}| description: {descriere}";
        }
        public override bool Equals(object obj)
        {
            if (obj is Task otherTask)
            {
                return taskID == otherTask.taskID && descriere == otherTask.descriere;
            }
            return false;
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(taskID, descriere);
        }
    }
}