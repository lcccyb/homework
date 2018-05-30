using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;

namespace hw2.ViewModels
{
    class TodoItemViewModel
    {
        private ObservableCollection<Models.TodoItem> allItems = new ObservableCollection<Models.TodoItem>();
        public System.Collections.ObjectModel.ObservableCollection<Models.TodoItem> AllItems { get { return this.allItems; } }

        private Models.TodoItem selectedItem = default(Models.TodoItem);
        public Models.TodoItem SelectedItem { get { return selectedItem; } set { this.selectedItem = value; } }

        public TodoItemViewModel()
        {
            ImageSource imgSource = new Windows.UI.Xaml.Media.Imaging.BitmapImage(new Uri("ms-appx:///Assets/2017-12-17.png"));

            this.allItems.Add(new Models.TodoItem("完成作业", "", DateTime.Now, imgSource));
            this.allItems.Add(new Models.TodoItem("完成作业", "", DateTime.Now, imgSource));
        }

        public void AddTodoItem(string title, string description, DateTime date,ImageSource img)
        {
            this.allItems.Add(new Models.TodoItem(title, description, date,img));
        }

        public void RemoveTodoItem(string id)
        {
            for (int i = 0; i < allItems.Count; i++)
            {
                if (allItems[i].id == id)
                {
                    this.allItems.RemoveAt(i);
                }
            }
            this.selectedItem = null;
        }

        public void UpdateTodoItem(string id, string title, string description, DateTime date,ImageSource img)
        {
            selectedItem.id = id;
            selectedItem.title = title;
            selectedItem.description = description;
            selectedItem.date = date;
            selectedItem.img = img;
            this.selectedItem = null;
        }
    }
}
