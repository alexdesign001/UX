namespace PresentationTheme.Aero.Win10
{
    using System;
    using System.Diagnostics;
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Controls.Primitives;

    /// <summary>
    ///   A <see cref="TabPanel"/> that supports
    ///   <see cref="FrameworkElement.UseLayoutRounding"/> and sets the
    ///   <see cref="TabItemKind"/> attached dependency property on contained
    ///   <see cref="TabItem"/> elements.
    /// </summary>
    public class RoundingTabPanel : TabPanel
    {
        private int headerCount;
        private int rowCount;
        private double rowHeight;

        /// <summary>
        ///   Identifies the <see cref="SelectedTab"/> dependency property.
        /// </summary>
        public static readonly DependencyProperty SelectedTabProperty =
            DependencyProperty.Register(
                nameof(SelectedTab),
                typeof(object),
                typeof(RoundingTabPanel),
                new FrameworkPropertyMetadata(
                    null,
                    FrameworkPropertyMetadataOptions.AffectsArrange));

        /// <summary>
        ///   Gets or sets the selected tab.
        /// </summary>
        public object SelectedTab
        {
            get => GetValue(SelectedTabProperty);
            set => SetValue(SelectedTabProperty, value);
        }

        /// <summary>
        ///   Identifies the <c>TabItemKind</c> attached dependency property.
        /// </summary>
        public static readonly DependencyProperty TabItemKindProperty =
            DependencyProperty.RegisterAttached(
                "TabItemKind",
                typeof(TabItemKind),
                typeof(RoundingTabPanel),
                new FrameworkPropertyMetadata(TabItemKind.Reference));

        /// <summary>
        ///   Gets the <see cref="TabItemKind"/> of the specified <see cref="TabItem"/>.
        /// </summary>
        /// <param name="item">
        ///   The item from which to read the property value.
        /// </param>
        /// <returns>
        ///   The value of the <c>TabItemKind</c> attached dependency property.
        /// </returns>
        public static TabItemKind GetTabItemKind(TabItem item)
        {
            if (item == null)
                throw new ArgumentNullException(nameof(item));
            return (TabItemKind)item.GetValue(TabItemKindProperty);
        }

        /// <summary>
        ///   Sets the <see cref="TabItemKind"/> of the specified <see cref="TabItem"/>.
        /// </summary>
        /// <param name="item">
        ///   The item from which to read the property value.
        /// </param>
        /// <param name="kind">The property value to set.</param>
        public static void SetTabItemKind(TabItem item, TabItemKind kind)
        {
            if (item == null)
                throw new ArgumentNullException(nameof(item));
            item.SetValue(TabItemKindProperty, kind);
        }

        private Dock TabStripPlacement
        {
            get
            {
                if (TemplatedParent is TabControl parent)
                    return parent.TabStripPlacement;
                return Dock.Top;
            }
        }

        /// <inheritdoc/>
        protected override Size MeasureOverride(Size constraint)
        {
            var contentSize = new Size();
            Dock tabAlignment = TabStripPlacement;

            rowCount = 1;
            headerCount = 0;
            rowHeight = 0;

            // For top and bottom placement the panel flows its children to
            // calculate the number of rows and desired vertical size
            if (tabAlignment == Dock.Top || tabAlignment == Dock.Bottom) {
                int numInCurrentRow = 0;
                double currentRowWidth = 0;
                double maxRowWidth = 0;
                foreach (UIElement child in InternalChildren) {
                    if (child.Visibility == Visibility.Collapsed)
                        continue;

                    ++headerCount;

                    // Helper measures child, and deals with Min, Max, and base Width & Height properties.
                    // Helper returns the size a child needs to take up (DesiredSize or property specified size).
                    child.Measure(constraint);
                    Size childSize = GetDesiredSizeWithoutMargin(child);

                    if (rowHeight < childSize.Height)
                        rowHeight = childSize.Height;

                    if (currentRowWidth + childSize.Width > constraint.Width && numInCurrentRow > 0) { // If child does not fit in the current row - create a new row
                        if (maxRowWidth < currentRowWidth)
                            maxRowWidth = currentRowWidth;

                        currentRowWidth = childSize.Width;
                        numInCurrentRow = 1;
                        ++rowCount;
                    } else {
                        currentRowWidth += childSize.Width;
                        ++numInCurrentRow;
                    }
                }

                if (maxRowWidth < currentRowWidth)
                    maxRowWidth = currentRowWidth;

                contentSize.Height = rowHeight * rowCount;

                // If we don't have a constraint or content smaller than the
                // constraint width then size to content
                if (double.IsInfinity(contentSize.Width)
                    || double.IsNaN(contentSize.Width)
                    || maxRowWidth < constraint.Width)
                    contentSize.Width = maxRowWidth;
                else
                    contentSize.Width = constraint.Width;

            } else if (tabAlignment == Dock.Left || tabAlignment == Dock.Right) {
                foreach (UIElement child in InternalChildren) {
                    if (child.Visibility == Visibility.Collapsed)
                        continue;

                    ++headerCount;

                    // Helper measures child, and deals with Min, Max, and base Width & Height properties.
                    // Helper returns the size a child needs to take up (DesiredSize or property specified size).
                    child.Measure(constraint);

                    Size childSize = GetDesiredSizeWithoutMargin(child);

                    if (contentSize.Width < childSize.Width)
                        contentSize.Width = childSize.Width;

                    contentSize.Height += childSize.Height;
                }
            }

            // Returns our minimum size & sets DesiredSize.
            return contentSize;
        }

        /// <inheritdoc/>
        protected override Size ArrangeOverride(Size arrangeSize)
        {
            switch (TabStripPlacement) {
                case Dock.Top:
                case Dock.Bottom:
                    ArrangeHorizontal(arrangeSize);
                    break;

                case Dock.Left:
                case Dock.Right:
                    ArrangeVertical(arrangeSize);
                    break;
            }

            return arrangeSize;
        }

        private void ArrangeHorizontal(Size arrangeSize)
        {
            Dock tabAlignment = TabStripPlacement;
            bool isMultiRow = rowCount > 1;
            int activeRow = 0;
            int[] solution = new int[0];
            var childOffset = new Vector();
            double[] headerSize = GetHeadersSize();

            // If we have multirows, then calculate the best header distribution
            if (isMultiRow) {
                solution = CalculateHeaderDistribution(arrangeSize.Width, headerSize);
                activeRow = GetActiveRow(solution);

                // TabPanel starts to layout children depending on activeRow
                // which should be always on bottom (top).
                // The first row should start from Y = (rowCount - 1 - activeRow) * rowHeight
                if (tabAlignment == Dock.Top)
                    childOffset.Y = (rowCount - 1 - activeRow) * rowHeight;

                if (tabAlignment == Dock.Bottom && activeRow != 0)
                    childOffset.Y = (rowCount - activeRow) * rowHeight;
            }

            int childIndex = 0;
            int separatorIndex = 0;
            TabItemKind kind = TabItemKind.Leading;
            foreach (UIElement child in InternalChildren) {
                if (child.Visibility == Visibility.Collapsed)
                    continue;

                var margin = (Thickness)child.GetValue(MarginProperty);
                double leftOffset = margin.Left;
                double rightOffset = margin.Right;
                double topOffset = margin.Top;
                double bottomOffset = margin.Bottom;

                bool lastHeaderInRow = isMultiRow && (separatorIndex < solution.Length && solution[separatorIndex] == childIndex || childIndex == headerCount - 1);

                var cellSize = new Size(headerSize[childIndex], rowHeight);

                // Align the last header in the row; If headers are not aligned
                // directional nav would not work correctly
                if (lastHeaderInRow)
                    cellSize.Width = arrangeSize.Width - childOffset.X;

                child.Arrange(new Rect(childOffset.X, childOffset.Y, cellSize.Width, cellSize.Height));

                if ((bool)child.GetValue(TabItem.IsSelectedProperty)) {
                    child.SetValue(TabItemKindProperty, TabItemKind.Reference);
                    kind = TabItemKind.Trailing;
                } else if (lastHeaderInRow && kind == TabItemKind.Leading) {
                    child.SetValue(TabItemKindProperty, TabItemKind.Reference);
                } else {
                    child.SetValue(TabItemKindProperty, kind);
                }

                if (lastHeaderInRow)
                    kind = TabItemKind.Leading;

                Size childSize = cellSize;
                childSize.Width = Math.Max(0d, childSize.Width - leftOffset - rightOffset);
                childSize.Height = Math.Max(0d, childSize.Height - topOffset - bottomOffset);

                // Calculate the offset for the next child
                childOffset.X += cellSize.Width;
                if (lastHeaderInRow) {
                    if ((separatorIndex == activeRow && tabAlignment == Dock.Top) ||
                        (separatorIndex == activeRow - 1 && tabAlignment == Dock.Bottom))
                        childOffset.Y = 0d;
                    else
                        childOffset.Y += rowHeight;

                    childOffset.X = 0d;
                    ++separatorIndex;
                }

                ++childIndex;
            }
        }

        private void ArrangeVertical(Size arrangeSize)
        {
            double y = 0.0;
            TabItemKind kind = TabItemKind.Leading;
            foreach (UIElement child in InternalChildren) {
                if (child.Visibility == Visibility.Collapsed)
                    continue;

                if ((bool)child.GetValue(TabItem.IsSelectedProperty)) {
                    child.SetValue(TabItemKindProperty, TabItemKind.Reference);
                    kind = TabItemKind.Trailing;
                } else {
                    child.SetValue(TabItemKindProperty, kind);
                }

                Size childSize = GetDesiredSizeWithoutMargin(child);
                child.Arrange(new Rect(0.0, y, arrangeSize.Width, childSize.Height));
                y += childSize.Height;
            }
        }

        private Size GetDesiredSizeWithoutMargin(UIElement element)
        {
            var thickness = (Thickness)element.GetValue(MarginProperty);
            return new Size(
                Math.Max(0, element.DesiredSize.Width - thickness.Left - thickness.Right),
                Math.Max(0, element.DesiredSize.Height - thickness.Top - thickness.Bottom));
        }

        private double[] GetHeadersSize()
        {
            var headerSize = new double[headerCount];
            int childIndex = 0;
            foreach (UIElement child in InternalChildren) {
                if (child.Visibility == Visibility.Collapsed)
                    continue;

                Size childSize = GetDesiredSizeWithoutMargin(child);
                headerSize[childIndex] = childSize.Width;
                ++childIndex;
            }
            return headerSize;
        }

        private int GetActiveRow(int[] solution)
        {
            int activeRow = 0;
            int childIndex = 0;
            if (solution.Length > 0) {
                foreach (UIElement child in InternalChildren) {
                    if (child.Visibility == Visibility.Collapsed)
                        continue;

                    bool isActiveTab = (bool)child.GetValue(Selector.IsSelectedProperty);

                    if (isActiveTab) {
                        return activeRow;
                    }

                    if (activeRow < solution.Length && solution[activeRow] == childIndex) {
                        ++activeRow;
                    }

                    ++childIndex;
                }
            }

            // If the is no selected element and aligment is Top  - then the active row is the last row
            if (TabStripPlacement == Dock.Top)
                activeRow = rowCount - 1;

            return activeRow;
        }

        private int[] CalculateHeaderDistribution(double rowWidthLimit, double[] headerWidth)
        {
            // TabPanel layout calculation (taken from the reference source):
            // Input: Row width and width of all headers
            // Output: int array which size is the number of separators and contains each separator position
            //
            // After measure call we have:
            // rowWidthLimit - width of the TabPanel
            // Header[0..n-1]  - headers
            // headerWidth[0..n-1] - header width
            //
            // Calculated values:
            // numSeparators                       - number of separators between numSeparators+1 rows
            // rowWidth[0..numSeparators]          - row width
            // rowHeaderCount[0..numSeparators]    - Row Count = number of headers on that row
            // rowAverageGap[0..numSeparators]     - Average Gap for the row i = (rowWidth - rowWidth[i])/rowHeaderCount[i]
            // currentSolution[0..numSeparators-1] - separator currentSolution[i]=x means Header[x] and h[x+1] are separated with new line
            // bestSolution[0..numSeparators-1]    - keep the last Best Solution
            // bestSolutionRowAverageGap           - keep the last Best Solution Average Gap
            //
            // Between all separators distribution the best solution have minimum Average Gap -
            // this is the amount of pixels added to the header (to justify) in the row
            //
            // How does it work:
            // First we flow the headers to calculate the number of necessary rows (numSeparators+1).
            // That means we need to insert numSeparators separators between n headers (numSeparators&lt;n always).
            // For each current state rowAverageGap[1..numSeparators+1] are calculated for each row.
            // Current state rowAverageGap = MAX (rowAverageGap[1..numSeparators+1]).
            // Our goal is to find the solution with MIN (rowAverageGap).
            // On each iteration step we move a header from a previous row to the row with maximum rowAverageGap.
            // We countinue the itterations only if we move to better solution, i.e. rowAverageGap is smaller.
            // Maximum iteration steps are less the number of headers.

            bool useLayoutRounding = UseLayoutRounding;
            double dpiX = LayoutHelper.GetDpiX(this);

            double bestSolutionMaxRowAverageGap = 0;
            int numHeaders = headerWidth.Length;

            int numSeparators = rowCount - 1;
            double currentRowWidth = 0;
            int numberOfHeadersInCurrentRow = 0;
            double currentAverageGap;
            int[] currentSolution = new int[numSeparators];
            int[] bestSolution = new int[numSeparators];
            int[] rowHeaderCount = new int[rowCount];
            double[] rowWidth = new double[rowCount];
            double[] rowAverageGap = new double[rowCount];
            double[] bestSolutionRowAverageGap = new double[rowCount];

            // Initialize the current state; Do the initial flow of the headers
            int currentRowIndex = 0;

            for (int index = 0; index < numHeaders; ++index) {
                if (currentRowWidth + headerWidth[index] > rowWidthLimit && numberOfHeadersInCurrentRow > 0) { // if we cannot add next header - flow to next row
                    // Store current row before we go to the next
                    rowWidth[currentRowIndex] = currentRowWidth; // Store the current row width
                    rowHeaderCount[currentRowIndex] = numberOfHeadersInCurrentRow; // For each row we store the number os headers inside
                    currentAverageGap = Math.Max(0d, (rowWidthLimit - currentRowWidth) / numberOfHeadersInCurrentRow); // The amout of width that should be added to justify the header
                    rowAverageGap[currentRowIndex] = currentAverageGap;
                    currentSolution[currentRowIndex] = index - 1; // Separator points to the last header in the row
                    if (bestSolutionMaxRowAverageGap < currentAverageGap) // Remember the maximum of all currentAverageGap
                        bestSolutionMaxRowAverageGap = currentAverageGap;

                    // Iterate to next row
                    currentRowIndex++;
                    currentRowWidth = headerWidth[index]; // Accumulate header widths on the same row
                    numberOfHeadersInCurrentRow = 1;
                } else {
                    currentRowWidth += headerWidth[index]; // Accumulate header widths on the same row
                    // Increase the number of headers only if they are not collapsed (width=0)
                    if (headerWidth[index] != 0)
                        ++numberOfHeadersInCurrentRow;
                }
            }

            // If everything fits in 1 row then exit (no separators needed)
            if (currentRowIndex == 0)
                return new int[0];

            // Add the last row
            rowWidth[currentRowIndex] = currentRowWidth;
            rowHeaderCount[currentRowIndex] = numberOfHeadersInCurrentRow;
            currentAverageGap = (rowWidthLimit - currentRowWidth) / numberOfHeadersInCurrentRow;
            rowAverageGap[currentRowIndex] = currentAverageGap;
            if (bestSolutionMaxRowAverageGap < currentAverageGap)
                bestSolutionMaxRowAverageGap = currentAverageGap;

            currentSolution.CopyTo(bestSolution, 0); // Remember the first solution as initial bestSolution
            rowAverageGap.CopyTo(bestSolutionRowAverageGap, 0); // bestSolutionRowAverageGap is used in ArrangeOverride to calculate header sizes

            // Search for the best solution
            // The exit condition if when we cannot move header to the next row
            while (true) {
                // Find the row with maximum AverageGap
                int worstRowIndex = 0; // Keep the row index with maximum AverageGap
                double maxAG = 0;

                for (int i = 0; i < rowCount; ++i) {
                    if (maxAG < rowAverageGap[i]) {
                        maxAG = rowAverageGap[i];
                        worstRowIndex = i;
                    }
                }

                // If we are on the first row - cannot move from previous
                if (worstRowIndex == 0)
                    break;

                // From the row with maximum AverageGap we try to move a header from previous row
                int moveToRow = worstRowIndex;
                int moveFromRow = moveToRow - 1;
                int moveHeader = currentSolution[moveFromRow];
                double movedHeaderWidth = headerWidth[moveHeader];

                rowWidth[moveToRow] += movedHeaderWidth;

                // If the moved header cannot fit - exit. We have the best solution already.
                if (rowWidth[moveToRow] > rowWidthLimit)
                    break;

                // If header is moved successfully to the worst row
                // we update the arrays keeping the row state
                currentSolution[moveFromRow]--;
                rowHeaderCount[moveToRow]++;
                rowWidth[moveFromRow] -= movedHeaderWidth;
                rowHeaderCount[moveFromRow]--;
                rowAverageGap[moveFromRow] = (rowWidthLimit - rowWidth[moveFromRow]) / rowHeaderCount[moveFromRow];
                rowAverageGap[moveToRow] = (rowWidthLimit - rowWidth[moveToRow]) / rowHeaderCount[moveToRow];

                // EvaluateSolution:
                // If the current solution is better than bestSolution - keep it in bestSolution
                maxAG = 0;
                for (int i = 0; i < rowCount; ++i) {
                    if (maxAG < rowAverageGap[i]) {
                        maxAG = rowAverageGap[i];
                    }
                }

                if (maxAG < bestSolutionMaxRowAverageGap) {
                    bestSolutionMaxRowAverageGap = maxAG;
                    currentSolution.CopyTo(bestSolution, 0);
                    rowAverageGap.CopyTo(bestSolutionRowAverageGap, 0);
                }
            }

            double[] rowErrors = null;
            if (useLayoutRounding) {
                rowErrors = new double[bestSolutionRowAverageGap.Length];
                for (int i = 0; i < bestSolutionRowAverageGap.Length; ++i) {
                    double rounded = LayoutHelper.FloorLayoutValue(bestSolutionRowAverageGap[i], dpiX);
                    rowErrors[i] = (bestSolutionRowAverageGap[i] - rounded) * rowHeaderCount[i];
                    bestSolutionRowAverageGap[i] = rounded;
                }
            }

            // Each header size should be increased so headers in the row stretch to fit the row
            currentRowIndex = 0;
            for (int index = 0; index < numHeaders; ++index) {
                headerWidth[index] += bestSolutionRowAverageGap[currentRowIndex];
                if (currentRowIndex < numSeparators && bestSolution[currentRowIndex] == index)
                    ++currentRowIndex;
            }

            if (useLayoutRounding) {
                double dpiIncrement = LayoutHelper.RoundLayoutValue(1, dpiX);
                currentRowIndex = 0;
                double error = rowErrors[currentRowIndex];
                for (int index = 0; index < numHeaders; ++index) {
                    if (error > 0) {
                        headerWidth[index] += dpiIncrement;
                        error -= dpiIncrement;
                    }
                    if (currentRowIndex < numSeparators && bestSolution[currentRowIndex] == index) {
                        Debug.Assert(error < dpiIncrement);
                        ++currentRowIndex;
                        error = rowErrors[currentRowIndex];
                    }
                }
            }

            // Use the best solution bestSolution[0..numSeparators-1] to layout
            return bestSolution;
        }
    }

    /// <summary>
    ///   Specifies the kind of a <see cref="TabItem"/> with respect to a reference
    ///   tab. The selected tab of a <see cref="TabControl"/> is automatically
    ///   the reference tab. If a tab row has no selected tab, the last tab is
    ///   used as reference.
    /// </summary>
    public enum TabItemKind
    {
        /// <summary>The tab is the reference tab.</summary>
        Reference,
        /// <summary>The tab is leading the reference tab.</summary>
        Leading,
        /// <summary>The tab is trailing the reference tab.</summary>
        Trailing
    }
}
