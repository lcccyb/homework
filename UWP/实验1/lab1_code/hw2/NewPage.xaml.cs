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
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Popups;
using Windows.Storage.Pickers;
using System.Threading.Tasks;
using Windows.UI.Xaml.Media.Imaging;
using Windows.Storage.Streams;



// “空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=234238 上有介绍

namespace hw2
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class NewPage : Page
    {
        public NewPage()
        {
            this.InitializeComponent();
            var viewTitleBar = Windows.UI.ViewManagement.ApplicationView.GetForCurrentView().TitleBar;
            viewTitleBar.BackgroundColor = Windows.UI.Colors.CornflowerBlue;
            viewTitleBar.ButtonBackgroundColor = Windows.UI.Colors.CornflowerBlue;
        }

        private ViewModels.TodoItemViewModel ViewModel;

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            ViewModel = ((ViewModels.TodoItemViewModel)e.Parameter);
            if (ViewModel.SelectedItem == null)
            {
                createButton.Content = "Create";
                //var i = new MessageDialog("Welcome!").ShowAsync();

            }
            else
            {
                createButton.Content = "Update";
                Title.Text = ViewModel.SelectedItem.title;
                Details.Text = ViewModel.SelectedItem.description;
                DatePicker1.Date = ViewModel.SelectedItem.date.Date;
                background.Source = ViewModel.SelectedItem.img;
            }
        }



        private void ScrollVier_ViewChanged(object sender, ScrollViewerViewChangedEventArgs e)
        {
            // Frame.Navigate(typeof(MainPage));
        }

        private void createButton_Click(object sender, RoutedEventArgs e)
        {
            if (!check()) return;

            if (createButton.Content as string == "Create")
                ViewModel.AddTodoItem(this.Title.Text, this.Details.Text, this.DatePicker1.Date.DateTime,this.background.Source);
            else ViewModel.UpdateTodoItem(ViewModel.SelectedItem.id, this.Title.Text, this.Details.Text, this.DatePicker1.Date.DateTime, this.background.Source);

            Frame.Navigate(typeof(MainPage), ViewModel);

        }

        private void DeleteButton_Clicked(object sender, RoutedEventArgs e)
        {
            if (ViewModel.SelectedItem != null)
            {
                ViewModel.RemoveTodoItem(ViewModel.SelectedItem.id);
                 Frame.Navigate(typeof(MainPage), ViewModel);
            }
        }

        private void cancelButton_Click(object sender, RoutedEventArgs e)
        { 
            if (ViewModel.SelectedItem != null)
            {             
                this.Title.Text = "";
                this.Details.Text = "";
                this.DatePicker1.Date = DateTime.Now;             
            }
        }

        private void UpdateButton_Clicked(object sender, RoutedEventArgs e)
        {
            if (ViewModel.SelectedItem != null)
            {
                ViewModel.UpdateTodoItem(ViewModel.SelectedItem.id ,ViewModel.SelectedItem.title,
                    ViewModel.SelectedItem.description, ViewModel.SelectedItem.date,ViewModel.SelectedItem.img);
                Frame.Navigate(typeof(MainPage), ViewModel);
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
            picker.FileTypeFilter.Add(".jpg");
            picker.FileTypeFilter.Add(".png");//添加可选择的文件类型，这个必须要设置
            StorageFile file = await picker.PickSingleFileAsync();    //只能选择一个文件

            if (file != null)
            {
                this.background.Source = await GetImageAsync(file);
            }

        }

        private bool check()
        {
            return check(this.Title.Text, "Title can't be empty!") && check(this.Details.Text, "Detail can't be empty!")
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
            if (this.DatePicker1.Date > DateTime.Now)
            {
                var i = new MessageDialog("DueDate is invalid!").ShowAsync();
                return false;
            }
            return true;
        }



    }
}

