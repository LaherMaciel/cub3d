#!/bin/bash

# Advanced README Analytics with Visual Elements
# Creates more sophisticated progress indicators and motivational elements

TEMP_README="README_ANALYTICS_TEMP.md"
ANALYTICS_SECTION="<!-- PROJECT_ANALYTICS -->"

# Check if we're in a git repository
if [ ! -d ".git" ]; then
    echo "Error: Not in a git repository"
    exit 1
fi

# Get comprehensive statistics
TOTAL_COMMITS=$(git rev-list --count HEAD)
TOTAL_AUTHORS=$(git log --pretty=format:"%an" | sort | uniq | wc -l)

# Get detailed commit counts
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

# Get recent activity
RECENT_COMMITS=$(git log --since="7 days ago" --oneline | wc -l)
RECENT_LAHER=$(git log --since="7 days ago" --author="Laher" --oneline | wc -l)
RECENT_KAYKI=$(git log --since="7 days ago" --author="Kayki" --oneline | wc -l)

# Get project duration
if [ -n "$(git log --reverse --pretty=format:"%ct" | head -1)" ]; then
    FIRST_COMMIT=$(git log --reverse --pretty=format:"%ct" | head -1)
    CURRENT_TIME=$(date +%s)
    PROJECT_DAYS=$(( (CURRENT_TIME - FIRST_COMMIT) / 86400 ))
else
    PROJECT_DAYS=0
fi

# Create advanced progress bars
create_advanced_progress_bar() {
    local percent=$1
    local width=25
    local filled=$((percent * width / 100))
    local empty=$((width - filled))
    
    printf "|"
    for i in $(seq 1 $filled); do printf "█"; done
    for i in $(seq 1 $empty); do printf "░"; done
    printf "| %3d%%" $percent
}

# Create emoji progress indicator
create_emoji_progress() {
    local percent=$1
    if [ $percent -ge 80 ]; then
        echo "🔥🔥🔥🔥🔥"
    elif [ $percent -ge 60 ]; then
        echo "🔥🔥🔥🔥⚡"
    elif [ $percent -ge 40 ]; then
        echo "🔥🔥🔥⚡⚡"
    elif [ $percent -ge 20 ]; then
        echo "🔥🔥⚡⚡⚡"
    else
        echo "🔥⚡⚡⚡⚡"
    fi
}

# Generate motivational message
get_motivational_message() {
    local laher_commits=$1
    local kayki_commits=$2
    local recent_commits=$3
    
    if [ $recent_commits -gt 10 ]; then
        echo "🚀 **ROCKET MODE** - You're on fire! Keep this energy!"
    elif [ $recent_commits -gt 5 ]; then
        echo "⚡ **HIGH VOLTAGE** - Great momentum! Don't stop now!"
    elif [ $recent_commits -gt 2 ]; then
        echo "📈 **STEADY CLIMB** - Good progress! Push a bit more!"
    elif [ $recent_commits -gt 0 ]; then
        echo "🐌 **SLOW BUT SURE** - Every step counts! Pick up the pace!"
    else
        echo "💤 **SLEEPING BEAUTY** - Time to wake up and code! ⏰"
    fi
}

# Generate competition message
get_competition_message() {
    local laher_commits=$1
    local kayki_commits=$2
    local diff=$((laher_commits - kayki_commits))
    
    if [ $diff -gt 10 ]; then
        echo "🏆 **Laher is DOMINATING** - Kayki, this is your chance to catch up! 🏃‍♂️💨"
    elif [ $diff -gt 5 ]; then
        echo "🥇 **Laher is ahead** - Kayki, time to step up your game! 🎯"
    elif [ $diff -lt -10 ]; then
        echo "🏆 **Kayki is DOMINATING** - Laher, don't let them win! 🏃‍♂️💨"
    elif [ $diff -lt -5 ]; then
        echo "🥇 **Kayki is ahead** - Laher, time to step up your game! 🎯"
    else
        echo "🤝 **Perfect Balance** - Great teamwork! Keep it up! 👥"
    fi
}

# Generate analytics section
cat > "$TEMP_README" << EOF
## 📊 Live Project Analytics

### 🏁 Development Race
| Developer | Commits | Percentage | Progress Bar | Energy Level |
|-----------|---------|------------|--------------|--------------|
| **Laher Maciel** | $LAHER_COMMITS | $LAHER_PERCENT% | $(create_advanced_progress_bar $LAHER_PERCENT) | $(create_emoji_progress $LAHER_PERCENT) |
| **Kayki Rocha** | $KAYKI_COMMITS | $KAYKI_PERCENT% | $(create_advanced_progress_bar $KAYKI_PERCENT) | $(create_emoji_progress $KAYKI_PERCENT) |
| **🤝 Collaborative** | $BOTH_COMMITS | $BOTH_PERCENT% | $(create_advanced_progress_bar $BOTH_PERCENT) | $(create_emoji_progress $BOTH_PERCENT) |

### 📈 Code Statistics Dashboard
- **📊 Total Commits**: \`$TOTAL_COMMITS\`
- **⏱️ Project Duration**: \`$PROJECT_DAYS days\`
- **➕ Lines Added**: \`$TOTAL_ADDED\`
- **➖ Lines Removed**: \`$TOTAL_REMOVED\`
- **🔄 Net Changes**: \`$NET_CHANGES\`
- **⚡ Recent Activity**: \`$RECENT_COMMITS commits\` (last 7 days)

### 🎯 Weekly Performance
| Developer | This Week | Last 7 Days |
|-----------|-----------|-------------|
| **Laher** | $RECENT_LAHER commits | $(create_emoji_progress $((RECENT_LAHER * 100 / 7))) |
| **Kayki** | $RECENT_KAYKI commits | $(create_emoji_progress $((RECENT_KAYKI * 100 / 7))) |

### 🚀 Development Velocity
EOF

# Add velocity indicators
if [ $PROJECT_DAYS -gt 0 ]; then
    DAILY_AVERAGE=$((TOTAL_COMMITS / PROJECT_DAYS))
    echo "- **📅 Average Commits/Day**: \`$DAILY_AVERAGE\`" >> "$TEMP_README"
    
    if [ $DAILY_AVERAGE -gt 5 ]; then
        echo "- **🔥 Velocity Status**: **BLAZING FAST** - You're coding machines!" >> "$TEMP_README"
    elif [ $DAILY_AVERAGE -gt 2 ]; then
        echo "- **⚡ Velocity Status**: **GOOD PACE** - Keep the momentum!" >> "$TEMP_README"
    else
        echo "- **🐌 Velocity Status**: **SLOW BURN** - Time to accelerate!" >> "$TEMP_README"
    fi
fi

# Add motivational sections
echo "" >> "$TEMP_README"
echo "### 🎮 Current Status" >> "$TEMP_README"
echo "$(get_motivational_message $LAHER_COMMITS $KAYKI_COMMITS $RECENT_COMMITS)" >> "$TEMP_README"

echo "" >> "$TEMP_README"
echo "### 🏆 Competition Status" >> "$TEMP_README"
echo "$(get_competition_message $LAHER_COMMITS $KAYKI_COMMITS)" >> "$TEMP_README"

# Add recent commits with emojis
echo "" >> "$TEMP_README"
echo "#### 📝 Recent Activity" >> "$TEMP_README"
echo "\`\`\`" >> "$TEMP_README"
git log --oneline -8 | sed 's/^/🔹 /' >> "$TEMP_README"
echo "\`\`\`" >> "$TEMP_README"

# Add file activity
echo "" >> "$TEMP_README"
echo "#### 📁 Most Active Files" >> "$TEMP_README"
echo "\`\`\`" >> "$TEMP_README"
git log --pretty=format: --name-only | sort | uniq -c | sort -rn | head -5 | sed 's/^/📄 /' >> "$TEMP_README"
echo "\`\`\`" >> "$TEMP_README"

# Add next goals
echo "" >> "$TEMP_README"
echo "#### 🎯 Next Milestones" >> "$TEMP_README"
echo "- [ ] **50 commits** - Halfway to greatness! 🎯" >> "$TEMP_README"
echo "- [ ] **100 commits** - Century club! 💯" >> "$TEMP_README"
echo "- [ ] **Perfect balance** - 50/50 collaboration! ⚖️" >> "$TEMP_README"
echo "- [ ] **Code quality** - Zero norminette errors! ✨" >> "$TEMP_README"

echo "" >> "$TEMP_README"
echo "---" >> "$TEMP_README"
echo "*🔄 Last updated: $(date) | Run \`make update-readme\` to refresh*" >> "$TEMP_README"
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

echo "Advanced README analytics updated successfully!"
