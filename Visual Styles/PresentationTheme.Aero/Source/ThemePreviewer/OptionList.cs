namespace ThemePreviewer
{
    using System;
    using System.Collections.ObjectModel;
    using System.Linq.Expressions;

    internal class OptionList : Collection<Option>
    {
        public EventHandler<StateEventArgs> StateChanged;

        public Option AddOption<TControl>(
            string name,
            TControl control,
            Expression<Func<TControl, bool>> propertyExpression,
            bool negated = false)
        {
            var option = Option.Create(new[] { control }, name, propertyExpression, negated);
            option.StateChanged += OnStateChanged;
            Add(option);

            return option;
        }

        public Option AddOption<TControl>(
            string name,
            TControl[] controls,
            Expression<Func<TControl, bool>> propertyExpression,
            bool negated = false)
        {
            var option = Option.Create(controls, name, propertyExpression, negated);
            option.StateChanged += OnStateChanged;
            Add(option);

            return option;
        }

        public Option AddOption<TControl>(
            string name,
            TControl control,
            Expression<Func<TControl, int>> propertyExpression)
        {
            if (!propertyExpression.CreateDelegates(out var getter, out var setter))
                throw new ArgumentException(nameof(propertyExpression));

            var option = new IntControlOption<TControl>(new[] { control }, name, getter, setter);
            Add(option);

            return option;
        }

        public Option AddOption<TControl>(
            string name,
            TControl control1,
            TControl control2,
            Expression<Func<TControl, int>> propertyExpression)
        {
            if (!propertyExpression.CreateDelegates(out var getter, out var setter))
                throw new ArgumentException(nameof(propertyExpression));

            var option = new IntControlOption<TControl>(new[] { control1, control2 }, name, getter, setter);
            Add(option);

            return option;
        }

        public Option AddOption<TControl, T>(
            string name,
            TControl control,
            Expression<Func<TControl, T>> propertyExpression,
            T trueValue,
            T falseValue)
        {
            var option = Option.Create(new[] { control }, name, propertyExpression, trueValue, falseValue);
            option.StateChanged += OnStateChanged;
            Add(option);

            return option;
        }

        public void AddOption<TControl>(
            string name, TControl control1, TControl control2,
            Expression<Func<TControl, bool>> expression, bool negated = false)
        {
            if (!negated)
                AddOption(name, control1, control2, expression, true, false);
            else
                AddOption(name, control1, control2, expression, false, true);
        }

        public void AddOption<TControl, T>(
            string name, TControl control1, TControl control2,
            Expression<Func<TControl, T>> expression, T trueValue, T falseValue)
        {
            var property = typeof(TControl).GetProperty(
                ((MemberExpression)expression.Body).Member.Name);
            if (property == null)
                throw new ArgumentException("propertyName");

            var getter = (Func<TControl, T>)property.GetGetMethod().CreateDelegate(typeof(Func<TControl, T>));
            var setter = (Action<TControl, T>)property.GetSetMethod().CreateDelegate(typeof(Action<TControl, T>));

            Func<bool> optGetter = () => getter(control1).Equals(trueValue);
            Action<bool> optSetter = value => {
                setter(control1, value ? trueValue : falseValue);
                setter(control2, value ? trueValue : falseValue);
            };

            Add(new GenericBoolOption(name, optGetter, optSetter));
        }

        public Option AddEnumOption<TControl, T>(
            string name,
            TControl control,
            Expression<Func<TControl, T>> expression)
        {
            var property = typeof(TControl).GetProperty(
                ((MemberExpression)expression.Body).Member.Name);
            if (property == null)
                throw new ArgumentException("propertyName");

            var getter = (Func<TControl, T>)property.GetGetMethod().CreateDelegate(typeof(Func<TControl, T>));
            var setter = (Action<TControl, T>)property.GetSetMethod().CreateDelegate(typeof(Action<TControl, T>));

            Func<T> optGetter = () => getter(control);
            Action<T> optSetter = value => setter(control, value);

            var option = new EnumOption<T>(name, optGetter, optSetter);
            Add(option);

            return option;
        }

        private void OnStateChanged(object sender, StateEventArgs e)
        {
            StateChanged?.Invoke(sender, e);
            RereadOptions();
        }

        private void RereadOptions()
        {
            foreach (var option in this)
                option.Refresh();
        }
    }
}
