#!/bin/bash

# Update README with project analytics
# This script generates visual progress indicators and statistics

TEMP_README="README_TEMP.md"
ANALYTICS_SECTION="<!-- PROJECT_ANALYTICS -->"

# Check if we're in a git repository
if [ ! -d ".git" ]; then
    echo "Error: Not in a git repository"
    exit 1
fi

# Get project statistics
TOTAL_COMMITS=$(git rev-list --count HEAD)
TOTAL_AUTHORS=$(git log --pretty=format:"%an" | sort | uniq | wc -l)

# Get commit counts per author
LAHER_COMMITS=$(git log --author="Laher" --oneline | wc -l)
KAYKI_COMMITS=$(git log --author="Kayki" --oneline | wc -l)
BOTH_COMMITS=$(git log --grep="\[Both\]" --oneline | wc -l)

# Calculate percentages
if [ $TOTAL_COMMITS -gt 0 ]; then
    LAHER_PERCENT=$((LAHER_COMMITS * 100 / TOTAL_COMMITS))
    KAYKI_PERCENT=$((KAYKI_COMMITS * 100 / TOTAL_COMMITS))
    BOTH_PERCENT=$((BOTH_COMMITS * 100 / TOTAL_COMMITS))
else
    LAHER_PERCENT=0
    KAYKI_PERCENT=0
    BOTH_PERCENT=0
fi

# Get lines of code statistics
TOTAL_ADDED=$(git log --pretty=tformat: --numstat | awk '{add += $1} END {print add+0}')
TOTAL_REMOVED=$(git log --pretty=tformat: --numstat | awk '{subs += $2} END {print subs+0}')
NET_CHANGES=$((TOTAL_ADDED - TOTAL_REMOVED))

# Get recent activity (last 7 days)
RECENT_COMMITS=$(git log --since="7 days ago" --oneline | wc -l)

# Get project duration
if [ -n "$(git log --reverse --pretty=format:"%ct" | head -1)" ]; then
    FIRST_COMMIT=$(git log --reverse --pretty=format:"%ct" | head -1)
    CURRENT_TIME=$(date +%s)
    PROJECT_DAYS=$(( (CURRENT_TIME - FIRST_COMMIT) / 86400 ))
else
    PROJECT_DAYS=0
fi

# Create progress bars
create_progress_bar() {
    local percent=$1
    local width=20
    local filled=$((percent * width / 100))
    local empty=$((width - filled))
    
    printf "["
    for i in $(seq 1 $filled); do printf "█"; done
    for i in $(seq 1 $empty); do printf "░"; done
    printf "] %d%%" $percent
}

# Generate analytics section
cat > "$TEMP_README" << EOF
## 📊 Project Analytics

### Development Progress
| Developer | Commits | Percentage | Progress |
|-----------|---------|------------|----------|
| **Laher Maciel** | $LAHER_COMMITS | $LAHER_PERCENT% | $(create_progress_bar $LAHER_PERCENT) |
| **Kayki Rocha** | $KAYKI_COMMITS | $KAYKI_PERCENT% | $(create_progress_bar $KAYKI_PERCENT) |
| **Collaborative** | $BOTH_COMMITS | $BOTH_PERCENT% | $(create_progress_bar $BOTH_PERCENT) |

### Code Statistics
- **Total Commits**: $TOTAL_COMMITS
- **Project Duration**: $PROJECT_DAYS days
- **Lines Added**: $TOTAL_ADDED
- **Lines Removed**: $TOTAL_REMOVED
- **Net Changes**: $NET_CHANGES
- **Recent Activity**: $RECENT_COMMITS commits (last 7 days)

### Development Velocity
EOF

# Add velocity indicators
if [ $PROJECT_DAYS -gt 0 ]; then
    DAILY_AVERAGE=$((TOTAL_COMMITS / PROJECT_DAYS))
    echo "- **Average Commits/Day**: $DAILY_AVERAGE" >> "$TEMP_README"
fi

# Add recent commits
echo "" >> "$TEMP_README"
echo "#### Recent Commits" >> "$TEMP_README"
echo "\`\`\`" >> "$TEMP_README"
git log --oneline -10 >> "$TEMP_README"
echo "\`\`\`" >> "$TEMP_README"

# Add motivational message based on activity
echo "" >> "$TEMP_README"
echo "#### 🚀 Development Status" >> "$TEMP_README"

if [ $RECENT_COMMITS -gt 5 ]; then
    echo "🔥 **High Activity** - Great momentum!" >> "$TEMP_README"
elif [ $RECENT_COMMITS -gt 2 ]; then
    echo "⚡ **Good Progress** - Keep it up!" >> "$TEMP_README"
elif [ $RECENT_COMMITS -gt 0 ]; then
    echo "📈 **Steady Progress** - Every commit counts!" >> "$TEMP_README"
else
    echo "💤 **Quiet Period** - Time to get coding!" >> "$TEMP_README"
fi

# Add balance indicator
echo "" >> "$TEMP_README"
echo "#### ⚖️ Collaboration Balance" >> "$TEMP_README"
DIFF=$((LAHER_COMMITS - KAYKI_COMMITS))
if [ $DIFF -gt 5 ]; then
    echo "⚠️ **Laher is ahead** - Kayki, time to catch up! 🏃‍♂️" >> "$TEMP_README"
elif [ $DIFF -lt -5 ]; then
    echo "⚠️ **Kayki is ahead** - Laher, time to catch up! 🏃‍♂️" >> "$TEMP_README"
else
    echo "✅ **Well Balanced** - Great teamwork! 🤝" >> "$TEMP_README"
fi

echo "" >> "$TEMP_README"
echo "*Last updated: $(date)*" >> "$TEMP_README"
echo "" >> "$TEMP_README"

# Update README.md
if [ -f "README.md" ]; then
    # Remove old analytics section if it exists
    awk "/$ANALYTICS_SECTION/,/<!-- END_ANALYTICS -->/ { next } { print }" README.md > README_temp.md
    
    # Add new analytics section
    if grep -q "$ANALYTICS_SECTION" README.md; then
        # Replace existing section
        sed "/$ANALYTICS_SECTION/,/<!-- END_ANALYTICS -->/c\\
$ANALYTICS_SECTION\\
$(cat $TEMP_README)\\
<!-- END_ANALYTICS -->" README_temp.md > README.md
    else
        # Add new section at the end
        cat README_temp.md > README.md
        echo "" >> README.md
        echo "$ANALYTICS_SECTION" >> README.md
        cat "$TEMP_README" >> README.md
        echo "<!-- END_ANALYTICS -->" >> README.md
    fi
    
    rm README_temp.md
else
    echo "README.md not found"
    exit 1
fi

# Clean up
rm "$TEMP_README"

echo "README analytics updated successfully!"