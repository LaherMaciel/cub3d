#!/bin/bash

# Individual README Analytics
# Shows personal stats for the current user

TEMP_README="README_INDIVIDUAL_TEMP.md"
ANALYTICS_SECTION="<!-- INDIVIDUAL_ANALYTICS -->"

# Check if we're in a git repository
if [ ! -d ".git" ]; then
    exit 1
fi

# Get current user info
CURRENT_USER=$(git config user.name 2>/dev/null || echo "Unknown")
CURRENT_EMAIL=$(git config user.email 2>/dev/null || echo "unknown@example.com")

# Get personal statistics
PERSONAL_COMMITS=$(git log --author="$CURRENT_USER" --oneline 2>/dev/null | wc -l)
TOTAL_COMMITS=$(git rev-list --count HEAD 2>/dev/null || echo "0")

# Calculate personal percentage
if [ $TOTAL_COMMITS -gt 0 ]; then
    PERSONAL_PERCENT=$((PERSONAL_COMMITS * 100 / TOTAL_COMMITS))
else
    PERSONAL_PERCENT=0
fi

# Get personal lines of code
PERSONAL_ADDED=$(git log --author="$CURRENT_USER" --pretty=tformat: --numstat 2>/dev/null | awk '{add += $1} END {print add+0}')
PERSONAL_REMOVED=$(git log --author="$CURRENT_USER" --pretty=tformat: --numstat 2>/dev/null | awk '{subs += $2} END {print subs+0}')
PERSONAL_NET=$((PERSONAL_ADDED - PERSONAL_REMOVED))

# Get recent personal activity
PERSONAL_RECENT=$(git log --since="7 days ago" --author="$CURRENT_USER" --oneline 2>/dev/null | wc -l)

# Get project duration
if [ -n "$(git log --reverse --pretty=format:"%ct" 2>/dev/null | head -1)" ]; then
    FIRST_COMMIT=$(git log --reverse --pretty=format:"%ct" 2>/dev/null | head -1)
    CURRENT_TIME=$(date +%s)
    PROJECT_DAYS=$(( (CURRENT_TIME - FIRST_COMMIT) / 86400 ))
else
    PROJECT_DAYS=0
fi

# Create progress bar
create_progress_bar() {
    local percent=$1
    local width=25
    local filled=$((percent * width / 100))
    local empty=$((width - filled))
    
    printf "|"
    for i in $(seq 1 $filled); do printf "█"; done
    for i in $(seq 1 $empty); do printf "░"; done
    printf "| %3d%%" $percent
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

# Get motivational message
get_personal_motivation() {
    local recent_commits=$1
    local total_commits=$2
    
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

# Get personal goals
get_personal_goals() {
    local commits=$1
    local percent=$2
    
    if [ $commits -lt 10 ]; then
        echo "🎯 **Next Goal**: Reach 10 commits! You're at $commits"
    elif [ $commits -lt 25 ]; then
        echo "🎯 **Next Goal**: Reach 25 commits! You're at $commits"
    elif [ $commits -lt 50 ]; then
        echo "🎯 **Next Goal**: Reach 50 commits! You're at $commits"
    elif [ $commits -lt 100 ]; then
        echo "🎯 **Next Goal**: Reach 100 commits! You're at $commits"
    else
        echo "🏆 **Achievement Unlocked**: 100+ commits! You're a coding machine!"
    fi
}

# Generate individual analytics
cat > "$TEMP_README" << EOF
## 🎯 Personal Development Dashboard

### 👤 Your Profile
- **Name**: $CURRENT_USER
- **Email**: $CURRENT_EMAIL
- **Role**: Cub3D Developer

### 📊 Your Personal Stats
| Metric | Your Count | Project Total | Your Share |
|--------|------------|---------------|------------|
| **Commits** | $PERSONAL_COMMITS | $TOTAL_COMMITS | $PERSONAL_PERCENT% |
| **Lines Added** | $PERSONAL_ADDED | - | - |
| **Lines Removed** | $PERSONAL_REMOVED | - | - |
| **Net Changes** | $PERSONAL_NET | - | - |
| **Recent Activity** | $PERSONAL_RECENT commits | - | - |

### 🏆 Your Progress
| Category | Progress Bar | Energy Level |
|----------|--------------|--------------|
| **Overall Contribution** | $(create_progress_bar $PERSONAL_PERCENT) | $(create_emoji_progress $PERSONAL_PERCENT) |
| **This Week** | $(create_progress_bar $((PERSONAL_RECENT * 100 / 7))) | $(create_emoji_progress $((PERSONAL_RECENT * 100 / 7))) |

### 🎮 Your Status
$(get_personal_motivation $PERSONAL_RECENT $PERSONAL_COMMITS)

### 🎯 Your Goals
$(get_personal_goals $PERSONAL_COMMITS $PERSONAL_PERCENT)

### 📝 Your Recent Work
\`\`\`
EOF

# Add recent personal commits
git log --author="$CURRENT_USER" --oneline -8 2>/dev/null | sed 's/^/🔹 /' >> "$TEMP_README"
echo "\`\`\`" >> "$TEMP_README"

# Add personal file activity
echo "" >> "$TEMP_README"
echo "#### 📁 Your Most Active Files" >> "$TEMP_README"
echo "\`\`\`" >> "$TEMP_README"
git log --author="$CURRENT_USER" --pretty=format: --name-only 2>/dev/null | sort | uniq -c | sort -rn | head -5 | sed 's/^/📄 /' >> "$TEMP_README"
echo "\`\`\`" >> "$TEMP_README"

# Add personal milestones
echo "" >> "$TEMP_README"
echo "#### 🏅 Your Milestones" >> "$TEMP_README"
echo "- [ ] **10 commits** - First milestone! 🎯" >> "$TEMP_README"
echo "- [ ] **25 commits** - Quarter century! 🥉" >> "$TEMP_README"
echo "- [ ] **50 commits** - Half century! 🥈" >> "$TEMP_README"
echo "- [ ] **100 commits** - Century club! 🥇" >> "$TEMP_README"
echo "- [ ] **Perfect code** - Zero norminette errors! ✨" >> "$TEMP_README"

echo "" >> "$TEMP_README"
echo "---" >> "$TEMP_README"
echo "*🔄 Last updated: $(date) | Personal analytics for $CURRENT_USER*" >> "$TEMP_README"
echo "" >> "$TEMP_README"

# Update README.md
if [ -f "README.md" ]; then
    # Remove old individual analytics section if it exists
    awk "/$ANALYTICS_SECTION/,/<!-- END_INDIVIDUAL_ANALYTICS -->/ { next } { print }" README.md > README_temp.md 2>/dev/null
    
    # Add new individual analytics section
    if grep -q "$ANALYTICS_SECTION" README.md 2>/dev/null; then
        # Replace existing section
        sed "/$ANALYTICS_SECTION/,/<!-- END_INDIVIDUAL_ANALYTICS -->/c\\
$ANALYTICS_SECTION\\
$(cat $TEMP_README)\\
<!-- END_INDIVIDUAL_ANALYTICS -->" README_temp.md > README.md 2>/dev/null
    else
        # Add new section at the end
        cat README_temp.md > README.md 2>/dev/null
        echo "" >> README.md
        echo "$ANALYTICS_SECTION" >> README.md
        cat "$TEMP_README" >> README.md
        echo "<!-- END_INDIVIDUAL_ANALYTICS -->" >> README.md
    fi
    
    rm README_temp.md 2>/dev/null
fi

# Clean up
rm "$TEMP_README" 2>/dev/null

# Exit silently
exit 0
