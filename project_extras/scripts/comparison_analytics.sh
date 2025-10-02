#!/bin/bash

# Comparison Analytics - Shows both Laher and Kayki side by side
# This shows individual stats for both developers in comparison format

TEMP_README="README_COMPARISON_TEMP.md"
ANALYTICS_SECTION="<!-- COMPARISON_ANALYTICS -->"

# Check if we're in a git repository
if [ ! -d ".git" ]; then
    exit 1
fi

# Get both developers' info
LAHER_NAME="Laher Maciel"
KAYKI_NAME="Kayki Rocha"

# Get total project stats
TOTAL_COMMITS=$(git rev-list --count HEAD 2>/dev/null || echo "0")
TOTAL_ADDED=$(git log --pretty=tformat: --numstat 2>/dev/null | awk '{add += $1} END {print add+0}')
TOTAL_REMOVED=$(git log --pretty=tformat: --numstat 2>/dev/null | awk '{subs += $2} END {print subs+0}')
TOTAL_NET=$((TOTAL_ADDED - TOTAL_REMOVED))

# Get individual stats
LAHER_COMMITS=$(git log --author="Laher" --oneline 2>/dev/null | wc -l)
KAYKI_COMMITS=$(git log --author="Kayki" --oneline 2>/dev/null | wc -l)
BOTH_COMMITS=$(git log --grep="\[Both\]" --oneline 2>/dev/null | wc -l)

LAHER_ADDED=$(git log --author="Laher" --pretty=tformat: --numstat 2>/dev/null | awk '{add += $1} END {print add+0}')
KAYKI_ADDED=$(git log --author="Kayki" --pretty=tformat: --numstat 2>/dev/null | awk '{add += $1} END {print add+0}')

LAHER_REMOVED=$(git log --author="Laher" --pretty=tformat: --numstat 2>/dev/null | awk '{subs += $2} END {print subs+0}')
KAYKI_REMOVED=$(git log --author="Kayki" --pretty=tformat: --numstat 2>/dev/null | awk '{subs += $2} END {print subs+0}')

LAHER_NET=$((LAHER_ADDED - LAHER_REMOVED))
KAYKI_NET=$((KAYKI_ADDED - KAYKI_REMOVED))

# Get recent activity
LAHER_RECENT=$(git log --since="7 days ago" --author="Laher" --oneline 2>/dev/null | wc -l)
KAYKI_RECENT=$(git log --since="7 days ago" --author="Kayki" --oneline 2>/dev/null | wc -l)

# Get project duration
if [ -n "$(git log --reverse --pretty=format:"%ct" 2>/dev/null | head -1)" ]; then
    FIRST_COMMIT=$(git log --reverse --pretty=format:"%ct" 2>/dev/null | head -1)
    CURRENT_TIME=$(date +%s)
    PROJECT_DAYS=$(( (CURRENT_TIME - FIRST_COMMIT) / 86400 ))
else
    PROJECT_DAYS=0
fi

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

# Create progress bars
create_progress_bar() {
    local percent=$1
    local width=15
    local filled=$((percent * width / 100))
    local empty=$((width - filled))
    
    printf "["
    for i in $(seq 1 $filled); do printf "█"; done
    for i in $(seq 1 $empty); do printf "░"; done
    printf "] %d%%" $percent
}

# Create emoji progress
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

# Generate comparison analytics
cat > "$TEMP_README" << EOF
## 📊 Development Comparison Dashboard

### 🏁 Head-to-Head Competition
| Developer | Commits | Percentage | Progress | Energy |
|-----------|---------|------------|----------|--------|
| **$LAHER_NAME** | $LAHER_COMMITS | $LAHER_PERCENT% | $(create_progress_bar $LAHER_PERCENT) | $(create_emoji_progress $LAHER_PERCENT) |
| **$KAYKI_NAME** | $KAYKI_COMMITS | $KAYKI_PERCENT% | $(create_progress_bar $KAYKI_PERCENT) | $(create_emoji_progress $KAYKI_PERCENT) |
| **🤝 Collaborative** | $BOTH_COMMITS | $BOTH_PERCENT% | $(create_progress_bar $BOTH_PERCENT) | $(create_emoji_progress $BOTH_PERCENT) |

### 📈 Code Statistics Comparison
| Metric | Total | $LAHER_NAME | $KAYKI_NAME |
|--------|-------|-------------|-------------|
| **📊 Total Commits** | $TOTAL_COMMITS | $LAHER_COMMITS | $KAYKI_COMMITS |
| **⏱️ Project Duration** | $PROJECT_DAYS days | - | - |
| **➕ Lines Added** | $TOTAL_ADDED | $LAHER_ADDED | $KAYKI_ADDED |
| **➖ Lines Removed** | $TOTAL_REMOVED | $LAHER_REMOVED | $KAYKI_REMOVED |
| **🔄 Net Changes** | $TOTAL_NET | $LAHER_NET | $KAYKI_NET |
| **⚡ Recent Activity** | $((LAHER_RECENT + KAYKI_RECENT)) commits | $LAHER_RECENT commits | $KAYKI_RECENT commits |

### 🎯 Weekly Performance
| Developer | This Week | Energy Level | Status |
|-----------|-----------|--------------|--------|
| **$LAHER_NAME** | $LAHER_RECENT commits | $(create_emoji_progress $((LAHER_RECENT * 100 / 7))) | $(if [ $LAHER_RECENT -gt 5 ]; then echo "🔥 On Fire"; elif [ $LAHER_RECENT -gt 2 ]; then echo "⚡ Active"; else echo "😴 Quiet"; fi) |
| **$KAYKI_NAME** | $KAYKI_RECENT commits | $(create_emoji_progress $((KAYKI_RECENT * 100 / 7))) | $(if [ $KAYKI_RECENT -gt 5 ]; then echo "🔥 On Fire"; elif [ $KAYKI_RECENT -gt 2 ]; then echo "⚡ Active"; else echo "😴 Quiet"; fi) |

### 🏆 Competition Status
EOF

# Add competition analysis
DIFF=$((LAHER_COMMITS - KAYKI_COMMITS))
if [ $DIFF -gt 5 ]; then
    echo "🥇 **$LAHER_NAME is DOMINATING** - $KAYKI_NAME, time to catch up! 🏃‍♂️💨" >> "$TEMP_README"
elif [ $DIFF -gt 2 ]; then
    echo "🥈 **$LAHER_NAME is ahead** - $KAYKI_NAME, step up your game! 🎯" >> "$TEMP_README"
elif [ $DIFF -lt -5 ]; then
    echo "🥇 **$KAYKI_NAME is DOMINATING** - $LAHER_NAME, don't let them win! 🏃‍♂️💨" >> "$TEMP_README"
elif [ $DIFF -lt -2 ]; then
    echo "🥈 **$KAYKI_NAME is ahead** - $LAHER_NAME, step up your game! 🎯" >> "$TEMP_README"
else
    echo "🤝 **Perfect Balance** - Great teamwork! Keep it up! 👥" >> "$TEMP_README"
fi

# Add recent commits comparison
echo "" >> "$TEMP_README"
echo "#### 📝 Recent Activity Comparison" >> "$TEMP_README"
echo "**$LAHER_NAME's recent commits:**" >> "$TEMP_README"
echo "\`\`\`" >> "$TEMP_README"
git log --author="Laher" --oneline -5 2>/dev/null | sed 's/^/🔹 /' >> "$TEMP_README"
echo "\`\`\`" >> "$TEMP_README"
echo "" >> "$TEMP_README"
echo "**$KAYKI_NAME's recent commits:**" >> "$TEMP_README"
echo "\`\`\`" >> "$TEMP_README"
git log --author="Kayki" --oneline -5 2>/dev/null | sed 's/^/🔹 /' >> "$TEMP_README"
echo "\`\`\`" >> "$TEMP_README"

# Add file activity comparison
echo "" >> "$TEMP_README"
echo "#### 📁 Most Active Files (Both Developers)" >> "$TEMP_README"
echo "\`\`\`" >> "$TEMP_README"
git log --pretty=format: --name-only 2>/dev/null | sort | uniq -c | sort -rn | head -8 | sed 's/^/📄 /' >> "$TEMP_README"
echo "\`\`\`" >> "$TEMP_README"

# Add milestones
echo "" >> "$TEMP_README"
echo "#### 🎯 Team Milestones" >> "$TEMP_README"
echo "- [ ] **50 total commits** - Halfway to greatness! 🎯" >> "$TEMP_README"
echo "- [ ] **100 total commits** - Century club! 💯" >> "$TEMP_README"
echo "- [ ] **Perfect balance** - 50/50 collaboration! ⚖️" >> "$TEMP_README"
echo "- [ ] **Code quality** - Zero norminette errors! ✨" >> "$TEMP_README"

echo "" >> "$TEMP_README"
echo "---" >> "$TEMP_README"
echo "*🔄 Last updated: $(date) | Comparison analytics*" >> "$TEMP_README"
echo "" >> "$TEMP_README"

# Update README.md
if [ -f "README.md" ]; then
    # Remove old comparison analytics section if it exists
    awk "/$ANALYTICS_SECTION/,/<!-- END_COMPARISON_ANALYTICS -->/ { next } { print }" README.md > README_temp.md 2>/dev/null
    
    # Add new comparison analytics section
    if grep -q "$ANALYTICS_SECTION" README.md 2>/dev/null; then
        # Replace existing section
        sed "/$ANALYTICS_SECTION/,/<!-- END_COMPARISON_ANALYTICS -->/c\\
$ANALYTICS_SECTION\\
$(cat $TEMP_README)\\
<!-- END_COMPARISON_ANALYTICS -->" README_temp.md > README.md 2>/dev/null
    else
        # Add new section at the end
        cat README_temp.md > README.md 2>/dev/null
        echo "" >> README.md
        echo "$ANALYTICS_SECTION" >> README.md
        cat "$TEMP_README" >> README.md
        echo "<!-- END_COMPARISON_ANALYTICS -->" >> README.md
    fi
    
    rm README_temp.md 2>/dev/null
fi

# Clean up
rm "$TEMP_README" 2>/dev/null

# Exit silently
exit 0
