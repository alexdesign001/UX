namespace PresentationTheme.Aero
{
    using System;
    using System.Globalization;
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Data;

    /// <summary>
    ///   Converts a <see cref="TreeViewItem"/> to its level in the hierarchy of
    ///   its <see cref="TreeView"/>.
    /// </summary>
    [ValueConversion(typeof(TreeViewItem), typeof(int), ParameterType = typeof(int))]
    public class TreeViewItemLevelConverter : DependencyObject, IValueConverter
    {
        /// <summary>
        ///   Converts a <see cref="TreeViewItem"/> to its level in the hierarchy
        ///   of its <see cref="TreeView"/>. Also sets the
        ///   <see cref="TreeViewService.ItemLevelProperty"/> on each converted
        ///   <see cref="TreeViewItem"/>.
        /// </summary>
        /// <param name="value">The value produced by the binding source.</param>
        /// <param name="targetType">
        ///   The type of the binding target property.
        /// </param>
        /// <param name="parameter">
        ///   An optional <see cref="int"/> or <see cref="double"/> factor.
        /// </param>
        /// <param name="culture">
        ///   The culture to use in the converter. <b>Not used.</b>
        /// </param>
        /// <returns>
        ///   The level of the <see cref="TreeViewItem"/>, multiplied by the
        ///   factor specified by <paramref name="parameter"/> if provided. The
        ///   level of root items is 0.
        /// </returns>
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (!(value is TreeViewItem item))
                return DependencyProperty.UnsetValue;

            int level = GetItemLevel(item);
            TreeViewService.SetItemLevel(item, level);

            if (parameter is int i)
                return level * i;

            if (parameter is double d)
                return level * d;

            return level;
        }

        object IValueConverter.ConvertBack(
            object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotSupportedException();
        }

        private int GetItemLevel(TreeViewItem item)
        {
            var parent = GetParentItem(item);
            if (parent != null)
                return TreeViewService.GetItemLevel(parent) + 1;
            return 0;
        }

        private static TreeViewItem GetParentItem(TreeViewItem item)
        {
            DependencyObject obj = item;
            for (obj = obj.GetVisualOrLogicalParent(); obj != null;
                 obj = obj.GetVisualOrLogicalParent()) {
                if (obj is TreeViewItem parentItem)
                    return parentItem;
                if (obj is TreeView)
                    break;
            }

            return null;
        }
    }
}
