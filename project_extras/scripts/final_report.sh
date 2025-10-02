#!/bin/bash

# Final Project Report Generator
# Generates comprehensive development statistics for the entire project

echo "=========================================="
echo "Cub3D - Final Project Development Report"
echo "=========================================="
echo "Generated on: $(date)"
echo ""

# Check if we're in a git repository
if [ ! -d ".git" ]; then
    echo "Error: Not in a git repository"
    exit 1
fi

echo "📊 OVERALL PROJECT STATISTICS"
echo "============================="
echo ""

# Total commits per author
echo "Total commits per developer:"
git shortlog -sn
echo ""

# Calculate total lines of code
echo "📈 CODE STATISTICS"
echo "=================="
echo "Total lines of code changes:"
git log --pretty=tformat: --numstat | \
awk '{ add += $1; subs += $2; loc += $1 - $2 } END { 
    printf "Total lines added: %s\n", add; 
    printf "Total lines removed: %s\n", subs; 
    printf "Net code changes: %s\n", loc 
}'
echo ""

# File statistics
echo "📁 FILE CONTRIBUTIONS"
echo "====================="
echo "Files with most changes:"
git log --pretty=format: --name-only | sort | uniq -c | sort -rn | head -20
echo ""

# Author activity breakdown
echo "👥 DEVELOPER ACTIVITY BREAKDOWN"
echo "==============================="
echo ""

# Get all authors
authors=$(git log --pretty=format:"%an" | sort | uniq)

for author in $authors; do
    echo "--- $author ---"
    
    # Commits by this author
    commits=$(git log --author="$author" --oneline | wc -l)
    echo "Total commits: $commits"
    
    # Lines added/removed by this author
    git log --author="$author" --pretty=tformat: --numstat | \
    awk '{ add += $1; subs += $2; loc += $1 - $2 } END { 
        printf "Lines added: %s\n", add; 
        printf "Lines removed: %s\n", subs; 
        printf "Net changes: %s\n", loc 
    }'
    
    # Files most modified by this author
    echo "Most modified files:"
    git log --author="$author" --pretty=format: --name-only | sort | uniq -c | sort -rn | head -5
    echo ""
done

# Development phases analysis
echo "🚀 DEVELOPMENT PHASES ANALYSIS"
echo "=============================="
echo ""

# Get commit dates and analyze phases
echo "Project timeline:"
git log --pretty=format:"%ad %s" --date=short | head -10
echo "..."

# Recent activity
echo "Recent development activity (last 30 days):"
git log --since="30 days ago" --pretty=format:"%ad %an: %s" --date=short
echo ""

# Pull request analysis (if available)
echo "🔀 COLLABORATION ANALYSIS"
echo "========================"
echo "Merge commits (collaborative work):"
git log --merges --pretty=format:"%ad %an: %s" --date=short | head -10
echo ""

# Branch analysis
echo "Branch development:"
git branch -r --sort=-committerdate | head -10
echo ""

# Code quality metrics
echo "🎯 CODE QUALITY METRICS"
echo "======================="
echo ""

# Check for norminette compliance
if command -v norminette &> /dev/null; then
    echo "Running norminette check..."
    make norm > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo "✅ Code style: Compliant with norminette"
    else
        echo "⚠️  Code style: Some norminette issues found"
    fi
else
    echo "ℹ️  Norminette not available for quality check"
fi

# Build success
echo "Build status:"
if make > /dev/null 2>&1; then
    echo "✅ Project builds successfully"
else
    echo "❌ Build issues detected"
fi

echo ""

# Generate summary
echo "📋 PROJECT SUMMARY"
echo "=================="
echo ""

total_commits=$(git rev-list --count HEAD)
total_authors=$(git log --pretty=format:"%an" | sort | uniq | wc -l)
project_days=$(( ($(date +%s) - $(git log --reverse --pretty=format:"%ct" | head -1)) / 86400 ))

echo "Project duration: $project_days days"
echo "Total commits: $total_commits"
echo "Active developers: $total_authors"
echo "Average commits per day: $(( total_commits / project_days ))"
echo ""

# Development distribution
echo "Development distribution:"
git log --pretty=format:"%an" | sort | uniq -c | sort -rn | while read count author; do
    percentage=$(( count * 100 / total_commits ))
    echo "  $author: $count commits ($percentage%)"
done

echo ""
echo "=========================================="
echo "Report generated successfully!"
echo "For detailed GitHub analytics, visit:"
echo "Repository → Insights → Contributors"
echo "=========================================="
