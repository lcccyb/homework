using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace hw2.Models
{
    class TodoItem
    {
        public string id { get; set; }
        public string title { get; set; }
        public string description { get; set; }
        public DateTime date { get; set; }
        public ImageSource img { set; get; }
        public bool completed { get; set; }

        public TodoItem(string title, string description, DateTime date, ImageSource img)
        {
            this.id = Guid.NewGuid().ToString(); 
            this.title = title;
            this.description = description;
            this.date = date;
            this.img = img;
            this.completed = false; 
        }
    }
}
