using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace myuwp.Models
{
    public class TodoItem
    {

        public String id;

        public String title { get; set; }

        public String description { get; set; }

        public Nullable<bool> completed { get; set; }

        public DateTime date { get; set; }

        public String path { get; set;}

        public TodoItem(String title, String description, DateTime date,bool complete, String path= null )
        {
            this.id = Guid.NewGuid().ToString(); //生成id
            this.title = title;
            this.description = description;
            this.completed = complete; //默认为未完成
            this.date = date;
            if (path == null) {
                this.path = @"Assets/background1.jpg";
            } else
            {
                this.path = path;
            }
        }
    }
}

