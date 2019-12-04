namespace PresentationTheme.Aero
{
    using System;
    using System.ComponentModel;
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Media;
    using System.Windows.Threading;

    /// <summary>
    ///   Provides various extensions for <see cref="TextBox"/> controls.
    /// </summary>
    public static class TextBoxService
    {
        private static readonly Type TextBoxViewType =
            typeof(TextBox).Assembly.GetType("System.Windows.Controls.TextBoxView");

        private static DependencyPropertyDescriptor contentPropertyDescriptor;

        private static DependencyPropertyDescriptor templatePropertyDescriptor;

        private static DependencyPropertyDescriptor ContentPropertyDescriptor =>
            contentPropertyDescriptor ??
            (contentPropertyDescriptor = DependencyPropertyDescriptor.FromProperty(
                ContentControl.ContentProperty, typeof(ScrollViewer)));

        private static DependencyPropertyDescriptor TemplatePropertyDescriptor =>
            templatePropertyDescriptor ??
            (templatePropertyDescriptor = DependencyPropertyDescriptor.FromProperty(
                Control.TemplateProperty, typeof(Control)));

        #region public attached Thickness ViewMargin
        /// <summary>
        ///   Identifies the ViewMargin dependency property.
        /// </summary>
        /// <remarks>
        ///   <see cref="TextBox"/> controls have a hardcoded margin of (0;2).
        ///   Setting this attached property on a <see cref="TextBox"/> allows
        ///   changing this margin.
        /// </remarks>
        public static readonly DependencyProperty ViewMarginProperty =
            DependencyProperty.RegisterAttached(
                "ViewMargin",
                typeof(Thickness?),
                typeof(TextBoxService),
                new PropertyMetadata(null, OnViewMarginChanged));

        /// <summary>
        ///   Gets the value of the attached <see cref="ViewMarginProperty"/>
        ///   for a specified <see cref="DependencyObject"/>.
        /// </summary>
        /// <param name="d">
        ///   The <see cref="DependencyObject"/> from which the property value
        ///   is read.
        /// </param>
        /// <returns>
        ///   The view margin for the <see cref="DependencyObject"/>.
        /// </returns>
        public static Thickness? GetViewMargin(DependencyObject d)
        {
            if (d == null)
                throw new ArgumentNullException(nameof(d));
            return (Thickness?)d.GetValue(ViewMarginProperty);
        }

        /// <summary>
        ///   Sets the value of the attached <see cref="ViewMarginProperty"/> to
        ///   a specified <see cref="DependencyObject"/>.
        /// </summary>
        /// <param name="d">
        ///   The <see cref="DependencyObject"/> to which the property is attached.
        /// </param>
        /// <param name="value">The view margin.</param>
        public static void SetViewMargin(DependencyObject d, Thickness? value)
        {
            if (d == null)
                throw new ArgumentNullException(nameof(d));
            d.SetValue(ViewMarginProperty, value);
        }

        private static void OnViewMarginChanged(
            DependencyObject d, DependencyPropertyChangedEventArgs args)
        {
            if (d is TextBox textBox) {
                if (args.NewValue != null)
                    Attach(textBox);
                else
                    Detach(textBox);
            }
        }
        #endregion

        private static void Attach(TextBox textBox)
        {
            textBox.Loaded += OnTextBoxLoaded;
            textBox.Unloaded += OnTextBoxUnloaded;
            if (textBox.IsLoaded)
                ApplyMargin(textBox);
        }

        private static void Detach(TextBox textBox)
        {
            textBox.Unloaded -= OnTextBoxUnloaded;
            textBox.Loaded -= OnTextBoxLoaded;
        }

        private static void OnTextBoxLoaded(object sender, RoutedEventArgs args)
        {
            var textBox = (TextBox)sender;
            TemplatePropertyDescriptor.AddValueChanged(
                textBox, OnTextBoxTemplateChanged);
            ApplyMargin(textBox);
        }

        private static void OnTextBoxUnloaded(object sender, RoutedEventArgs args)
        {
            var textBox = (TextBox)sender;
            TemplatePropertyDescriptor.RemoveValueChanged(
                textBox, OnTextBoxTemplateChanged);
            ApplyMargin(textBox);
        }

        private static void OnTextBoxTemplateChanged(object sender, EventArgs e)
        {
            var textBox = (TextBox)sender;
            if (textBox.IsLoaded)
                ApplyMargin(textBox);
        }

        private static void ApplyMargin(TextBox textBox, bool mayDefer = true)
        {
            if (textBox.Template.FindName("PART_ContentHost", textBox) is ScrollViewer contentHost) {
                if (contentHost.HasContent)
                    ApplyMargin(contentHost);
                else
                    ContentPropertyDescriptor.AddValueChanged(
                        contentHost, OnContentHostContentChanged);
            } else if (mayDefer) {
                textBox.Dispatcher.BeginInvoke(DispatcherPriority.Loaded, new Action(() => {
                    ApplyMargin(textBox, false);
                }));
            }
        }

        private static void OnContentHostContentChanged(object sender, EventArgs e)
        {
            var contentHost = (ScrollViewer)sender;
            ContentPropertyDescriptor.RemoveValueChanged(
                contentHost, OnContentHostContentChanged);
            ApplyMargin(contentHost);
        }

        private static void ApplyMargin(ScrollViewer contentHost)
        {
            var textBox = contentHost.FindAncestor<TextBox>();
            if (textBox != null && contentHost.Content is FrameworkElement element
                                && element.GetType() == TextBoxViewType) {
                var margin = GetViewMargin(textBox);
                if (margin != null)
                    element.Margin = margin.Value;
            }
        }

        internal static TAncestor FindAncestor<TAncestor>(this DependencyObject obj)
            where TAncestor : DependencyObject
        {
            if (obj == null)
                throw new ArgumentNullException(nameof(obj));

            for (obj = obj.GetVisualOrLogicalParent(); obj != null;
                 obj = obj.GetVisualOrLogicalParent()) {
                if (obj is TAncestor ancestor)
                    return ancestor;
            }

            return null;
        }

        internal static DependencyObject GetVisualOrLogicalParent(
            this DependencyObject sourceElement)
        {
            if (sourceElement == null)
                return null;
            if (sourceElement is Visual)
                return VisualTreeHelper.GetParent(sourceElement) ??
                       LogicalTreeHelper.GetParent(sourceElement);
            return LogicalTreeHelper.GetParent(sourceElement);
        }
    }
}
