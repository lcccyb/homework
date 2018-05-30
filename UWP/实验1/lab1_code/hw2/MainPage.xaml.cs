using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.UI.Core;
using Windows.UI.Popups;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.Storage.Pickers;
using System.Threading.Tasks;
using Windows.UI.Xaml.Media.Imaging;
using Windows.Storage.Streams;

//“空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 上有介绍

namespace hw2
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            var viewTitleBar = Windows.UI.ViewManagement.ApplicationView.GetForCurrentView().TitleBar;
            viewTitleBar.BackgroundColor = Windows.UI.Colors.CornflowerBlue;
            viewTitleBar.ButtonBackgroundColor = Windows.UI.Colors.CornflowerBlue;
            this.ViewModel = new ViewModels.TodoItemViewModel();
        }

        ViewModels.TodoItemViewModel ViewModel { get; set; }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            if (e.Parameter.GetType() == typeof(ViewModels.TodoItemViewModel))
            {
                this.ViewModel = (ViewModels.TodoItemViewModel)(e.Parameter);
            }
        }

        private void TodoItem_ItemClicked(object sender, ItemClickEventArgs e)
        { 
            ViewModel.SelectedItem = (Models.TodoItem)(e.ClickedItem);

            if (this.VisualStateGroup.CurrentState == VisualStateMin0) 
            {
                Frame.Navigate(typeof(NewPage), ViewModel);
            }
            else
            {
                updateButton.Content = "Update";
                this.Title.Text = ViewModel.SelectedItem.title;
                this.Detail.Text = ViewModel.SelectedItem.description;
                this.DueDate.Date = ViewModel.SelectedItem.date.Date;
                this.img.ImageSource = ViewModel.SelectedItem.img;
            }

        }


        private void AddAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            if (this.VisualStateGroup.CurrentState == VisualStateMin0) 
                 Frame.Navigate(typeof(NewPage), ViewModel);
        }

        private void checkBox1_checked(object sender, RoutedEventArgs e)
        {

            //this.line1.Visibility = Visibility.Visible;
        }
        private void checkBox1_unchecked(object sender, RoutedEventArgs e)
        {
            //this.line1.Visibility = Visibility.Collapsed;
        }

        private void MenuFlyoutItem_Click(object sender, RoutedEventArgs e)
        {

        }

        private void OnItemClick(object sender, RoutedEventArgs e)
        {
            if (ViewModel.SelectedItem != null)
            {
                ViewModel.RemoveTodoItem(ViewModel.SelectedItem.id);
            }
        }

        private void updateButton_Click(object sender, RoutedEventArgs e)
        {
            if (ViewModel.SelectedItem != null)
            {
                if (!check()) return;
                ViewModel.UpdateTodoItem(ViewModel.SelectedItem.id, this.Title.Text, this.Detail.Text, this.DueDate.Date.DateTime,this.img.ImageSource);
            }
            else
            {
                updateButton.Content = "Create";
                if (!check()) return;
                ViewModel.AddTodoItem(this.Title.Text, this.Detail.Text, this.DueDate.Date.DateTime,this.img.ImageSource);
            }
        }

        private void cancelButton_Click(object sender, RoutedEventArgs e)
        {
            if (ViewModel.SelectedItem != null)
            {
                this.Title.Text = String.Empty;
                this.Detail.Text = String.Empty;
                this.DueDate.Date = DateTime.Now.Date;
            }
        }

        public async Task<BitmapImage> GetImageAsync(StorageFile storageFile)
        {
            BitmapImage bitmapImage = new BitmapImage();
            FileRandomAccessStream stream = (FileRandomAccessStream)await storageFile.OpenAsync(FileAccessMode.Read);
            bitmapImage.SetSource(stream);
            return bitmapImage;
        }

        private async void SelectButton_Click(object sender, RoutedEventArgs e)
        {
            FileOpenPicker picker = new FileOpenPicker();
            picker.ViewMode = PickerViewMode.List;  //设置文件的现实方式，这里选择的是图标
            picker.SuggestedStartLocation = PickerLocationId.PicturesLibrary; //设置打开时的默认路径，这里选择的是图片库
            picker.FileTypeFilter.Add(".png");
            picker.FileTypeFilter.Add(".jpg");//添加可选择的文件类型，这个必须要设置
            StorageFile file = await picker.PickSingleFileAsync();    //只能选择一个文件

            if (file != null)
            {
                this.img.ImageSource = await GetImageAsync(file);
            }

        }

        private bool check()
        {
            return check(this.Title.Text, "Title can't be empty!") && check(this.Detail.Text, "Detail can't be empty!")
                   && checkDate();
        }
        private bool check(string text, string errorMessage)
        {
            if (string.IsNullOrEmpty(text))
            {
                var i = new MessageDialog(errorMessage).ShowAsync();
                return false;
            }
            return true;
        }
        private bool checkDate()
        {
            if(this.DueDate.Date > DateTime.Now)
            {
                var i = new MessageDialog("DueDate is invalid").ShowAsync();
                return false;
            }
            return true;
        }

    }
}
