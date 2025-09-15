#!/bin/bash

# Prepare project for submission
# This script removes all collaboration and analytics files

echo "=========================================="
echo "Preparing Cub3D for Submission"
echo "=========================================="
echo ""

# Create backup of current state
echo "📦 Creating backup of current project..."
if [ -d "project_extras" ]; then
    cp -r project_extras project_extras_backup
    echo "✅ Backup created: project_extras_backup/"
fi

# Remove collaboration files
echo "🗑️  Removing collaboration files..."
rm -f CONTRIBUTING.md CODEOWNERS PROJECT_ANALYTICS.md 2>/dev/null || true
rm -rf .github 2>/dev/null || true
rm -rf scripts 2>/dev/null || true
rm -rf project_extras 2>/dev/null || true

# Clean up analytics from README
echo "🧹 Cleaning README analytics..."
if [ -f "README.md" ]; then
    # Remove analytics section
    awk '/<!-- PROJECT_ANALYTICS -->/,/<!-- END_ANALYTICS -->/ { next } { print }' README.md > README_temp.md
    mv README_temp.md README.md
    echo "✅ README analytics removed"
fi

# Clean up analytics calls from Makefile
echo "🧹 Cleaning Makefile analytics calls..."
if [ -f "Makefile" ]; then
    # Remove analytics script calls
    sed -i '/@\.\/project_extras\/scripts\/update_analytics\.sh/d' Makefile
    echo "✅ Makefile analytics calls removed"
fi

# Clean build artifacts
echo "🧹 Cleaning build artifacts..."
rm -f .norminette.log 2>/dev/null || true
rm -f cub3d 2>/dev/null || true
rm -rf objects/ 2>/dev/null || true

# Show remaining files
echo ""
echo "📋 Remaining files for submission:"
echo "=================================="
ls -la | grep -E "^-" | awk '{print "📄 " $9}' | grep -v "^📄 \.$" | grep -v "^📄 \.\.$"

echo ""
echo "✅ Project ready for submission!"
echo ""
echo "📁 Mandatory files present:"
echo "  - src/ (source code)"
echo "  - include/ (headers)"
echo "  - libraries/ (libft, minilibx)"
echo "  - Makefile"
echo "  - .gitignore"
echo "  - README.md (clean, no analytics)"
echo ""
echo "💡 To restore collaboration features after submission:"
echo "  - Restore from backup: mv project_extras_backup project_extras"
echo "  - Run: make re"
echo ""
echo "=========================================="
