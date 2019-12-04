﻿using System.Collections.Generic;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls.Primitives;
using Xunit;
using Xunit.Sdk;

namespace MaterialDesignThemes.Wpf.Tests
{
    public class PopupBoxTests
    {
        [StaFact]
        [Description("Issue 1091")]
        public void ToggleButtonInheritsTabIndex()
        {
            var popupBox = new PopupBox { TabIndex = 3 };
            popupBox.ApplyDefaultStyle();

            ToggleButton togglePart = popupBox.FindVisualChild<ToggleButton>(PopupBox.TogglePartName);
            
            Assert.Equal(3, togglePart.TabIndex);
        }

        [StaFact]
        [Description("Issue 1231")]
        public void ToggleButtonInheritsIsTabStopWhenFalse()
        {
            var popupBox = new PopupBox { IsTabStop = false };
            popupBox.ApplyDefaultStyle();

            ToggleButton togglePart = popupBox.FindVisualChild<ToggleButton>(PopupBox.TogglePartName);

            Assert.Equal(false, togglePart.IsTabStop);
        }

        [StaFact]
        [Description("Issue 1231")]
        public void ToggleButtonInheritsIsTabStopWhenTrue()
        {
            var popupBox = new PopupBox { IsTabStop = true };
            popupBox.ApplyDefaultStyle();

            ToggleButton togglePart = popupBox.FindVisualChild<ToggleButton>(PopupBox.TogglePartName);

            Assert.Equal(true, togglePart.IsTabStop);
        }
    }
}