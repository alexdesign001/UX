// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

// DO NOT EDIT! This file was generated by CustomTasks.DependencyPropertyCodeGen
#pragma once

class RadioButtonsElementFactoryProperties
{
public:
    RadioButtonsElementFactoryProperties();

    void DataTemplate(winrt::DataTemplate const& value);
    winrt::DataTemplate DataTemplate();

    static winrt::DependencyProperty DataTemplateProperty() { return s_DataTemplateProperty; }

    static GlobalDependencyProperty s_DataTemplateProperty;

    static void EnsureProperties();
    static void ClearProperties();
};
