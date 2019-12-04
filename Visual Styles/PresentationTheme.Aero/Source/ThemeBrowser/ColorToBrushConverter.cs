namespace ThemeBrowser
{
    using System;
    using System.Globalization;
    using System.Windows.Data;
    using System.Windows.Media;

    public class ColorToBrushConverter : IValueConverter
    {
        public bool IgnoreAlpha { get; set; }

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (!(value is Color color) || !targetType.IsAssignableFrom(typeof(SolidColorBrush)))
                return Binding.DoNothing;

            if (IgnoreAlpha)
                color.A = 255;
            return new SolidColorBrush(color);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (!(value is SolidColorBrush brush) || targetType != typeof(Color))
                return Binding.DoNothing;

            return brush.Color;
        }
    }
}
