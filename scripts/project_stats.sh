#!/bin/bash

# Contribution Statistics Script
# Run this script to get detailed contribution statistics

echo "=========================================="
echo "Cub3D Contribution Statistics"
echo "=========================================="
echo ""

# Check if we're in a git repository
if [ ! -d ".git" ]; then
    echo "Error: Not in a git repository"
    exit 1
fi

echo "📊 OVERALL STATISTICS"
echo "===================="
echo ""

# Total commits per author
echo "Total commits per author:"
git shortlog -sn
echo ""

# Recent commits (last 30 days)
echo "📅 RECENT ACTIVITY (Last 30 days)"
echo "================================="
git log --since="30 days ago" --pretty=format:"%h %an %ad %s" --date=short
echo ""

# Lines of code statistics
echo "📈 CODE STATISTICS"
echo "=================="
echo "Lines added/removed in last 30 days:"
git log --since="30 days ago" --pretty=tformat: --numstat | \
awk '{ add += $1; subs += $2; loc += $1 - $2 } END { 
    printf "Added lines: %s\n", add; 
    printf "Removed lines: %s\n", subs; 
    printf "Net changes: %s\n", loc 
}'
echo ""

# File changes
echo "📁 FILE CHANGES (Last 30 days)"
echo "=============================="
git diff --stat HEAD~30 HEAD 2>/dev/null || echo "Not enough history for 30-day comparison"
echo ""

# Author activity
echo "👥 AUTHOR ACTIVITY"
echo "=================="
echo "Commits by author (last 30 days):"
git log --since="30 days ago" --pretty=format:"%an" | sort | uniq -c | sort -nr
echo ""

# Branch activity
echo "🌿 BRANCH ACTIVITY"
echo "=================="
echo "Recent branches:"
git branch -r --sort=-committerdate | head -10
echo ""

# Pull request activity (if available)
echo "🔀 PULL REQUEST ACTIVITY"
echo "========================"
echo "Recent merges:"
git log --merges --since="30 days ago" --pretty=format:"%h %an %ad %s" --date=short
echo ""

echo "=========================================="
echo "For more detailed stats, visit:"
echo "GitHub → Insights → Contributors"
echo "=========================================="
