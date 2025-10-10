#!/bin/bash

# Professional Project Analytics Generator
# Automatically detects team members from git repository and generates comprehensive analytics

TEMP_README="ANALYTICS_TEMP.md"
ANALYTICS_SECTION="<!-- PROJECT_ANALYTICS -->"

# Check if we're in a git repository
if [ ! -d ".git" ]; then
    exit 1
fi

# Get project statistics
TOTAL_COMMITS=$(git rev-list --count HEAD)
TOTAL_AUTHORS=$(git log --pretty=format:"%an" | sort | uniq | wc -l)

# Get commit counts for each team member
get_author_commits() {
    local author="$1"
    git log --author="$author" --oneline | wc -l
}

# Get lines of code statistics for each team member
get_author_stats() {
    local author="$1"
    local added=$(git log --author="$author" --pretty=tformat: --numstat | awk '{add += $1} END {print add+0}')
    local removed=$(git log --author="$author" --pretty=tformat: --numstat | awk '{subs += $2} END {print subs+0}')
    echo "$added $removed"
}

# Get recent activity for each team member (last 7 days)
get_recent_activity() {
    local author="$1"
    git log --since="7 days ago" --author="$author" --oneline | wc -l
}

# Get weekly code changes for each team member (last 7 days)
get_weekly_stats() {
    local author="$1"
    local added=$(git log --since="7 days ago" --author="$author" --pretty=tformat: --numstat | awk '{add += $1} END {print add+0}')
    local removed=$(git log --since="7 days ago" --author="$author" --pretty=tformat: --numstat | awk '{subs += $2} END {print subs+0}')
    echo "$added $removed"
}

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

# Create activity level indicator based on relative contribution (for overall project)
create_activity_level() {
    local added=$1
    local total_added=$2
    local removed=$3
    local total_changes=$((added + removed))
    
    if [ $total_changes -eq 0 ]; then
        echo "📝 **PENDING** - Awaiting contribution"
    elif [ $total_added -eq 0 ]; then
        echo "🔧 **INITIAL** - Starting project"
    else
        local contribution_percent=$((added * 100 / total_added))
        
        if [ $contribution_percent -le 5 ]; then
            echo "🔧 **INITIAL** - Early contribution ($contribution_percent%)"
        elif [ $contribution_percent -le 20 ]; then
            echo "⚙️ **DEVELOPING** - Building foundation ($contribution_percent%)"
        elif [ $contribution_percent -le 40 ]; then
            echo "🚀 **PROGRESSIVE** - Active development ($contribution_percent%)"
        elif [ $contribution_percent -le 60 ]; then
            echo "💪 **INTENSIVE** - Major contribution ($contribution_percent%)"
        elif [ $contribution_percent -le 80 ]; then
            echo "🏆 **EXCEPTIONAL** - Leading development ($contribution_percent%)"
        else
            echo "👑 **DOMINANT** - Primary contributor ($contribution_percent%)"
        fi
    fi
}

# Create weekly activity level indicator based on absolute numbers
create_weekly_activity_level() {
    local added=$1
    local removed=$2
    local total_changes=$((added + removed))
    
    if [ $total_changes -eq 0 ]; then
        echo "📝 **PENDING** - No activity this week"
    elif [ $total_changes -le 10 ]; then
        echo "🔧 **MINIMAL** - Light work ($total_changes lines)"
    elif [ $total_changes -le 50 ]; then
        echo "⚙️ **MODERATE** - Steady progress ($total_changes lines)"
    elif [ $total_changes -le 100 ]; then
        echo "🚀 **ACTIVE** - Good pace ($total_changes lines)"
    elif [ $total_changes -le 200 ]; then
        echo "💪 **INTENSIVE** - Strong work ($total_changes lines)"
    elif [ $total_changes -le 500 ]; then
        echo "🏆 **EXCEPTIONAL** - Major progress ($total_changes lines)"
    else
        echo "👑 **DOMINANT** - Outstanding week ($total_changes lines)"
    fi
}

# Create professional emoji progress indicator
create_emoji_progress() {
    local percent=$1
    if [ $percent -ge 90 ]; then
        echo "🚀🔥💯⚡🎯"
    elif [ $percent -ge 80 ]; then
        echo "🔥🔥🔥🔥⚡"
    elif [ $percent -ge 70 ]; then
        echo "🔥🔥🔥⚡⚡"
    elif [ $percent -ge 60 ]; then
        echo "🔥🔥⚡⚡⚡"
    elif [ $percent -ge 50 ]; then
        echo "🔥⚡⚡⚡⚡"
    elif [ $percent -ge 30 ]; then
        echo "⚡⚡⚡⚡⚡"
    elif [ $percent -ge 10 ]; then
        echo "🌱⚡⚡⚡⚡"
    else
        echo "💤⚡⚡⚡⚡"
    fi
}

# Generate professional motivational message
get_motivational_message() {
    local recent_commits=$1
    
    if [ $recent_commits -gt 15 ]; then
        echo "🚀 **EXCEPTIONAL PERFORMANCE** - Outstanding dedication! You're setting the bar high!"
    elif [ $recent_commits -gt 10 ]; then
        echo "🔥 **EXCELLENT MOMENTUM** - Great progress! Keep up the fantastic work!"
    elif [ $recent_commits -gt 5 ]; then
        echo "⚡ **STRONG ACTIVITY** - Good pace! Maintain this steady progress!"
    elif [ $recent_commits -gt 2 ]; then
        echo "📈 **CONSISTENT EFFORT** - Steady progress! Push for more commits!"
    elif [ $recent_commits -gt 0 ]; then
        echo "🐌 **MINIMAL ACTIVITY** - Every contribution counts! Increase your frequency!"
    else
        echo "💤 **INACTIVE PERIOD** - Time to re-engage! Let's get back to coding! ⏰"
    fi
}

# Generate professional competition message based on code changes
get_competition_message() {
    local max_changes=0
    local leader_idx=0
    local total_changes=0
    
    # Find the leader based on code changes
    for i in "${!TEAM_MEMBERS[@]}"; do
        local member="${TEAM_MEMBERS[$i]}"
        local stats=($(get_author_stats "$member"))
        local added=${stats[0]}
        local removed=${stats[1]}
        local net_changes=$((added - removed))
        total_changes=$((total_changes + net_changes))
        
        if [ "$net_changes" -gt "$max_changes" ]; then
            max_changes=$net_changes
            leader_idx=$i
        fi
    done
    
    local leader_name="${DISPLAY_NAMES[$leader_idx]}"
    
    if [ ${#TEAM_MEMBERS[@]} -eq 1 ]; then
        echo "👤 **SOLO DEVELOPER** - You're handling this project independently! Great work!"
    elif [ "$max_changes" -gt "$((total_changes / 2))" ]; then
        echo "🏆 **$leader_name is LEADING** - Strong code contribution! Others, time to step up! 🎯"
    else
        echo "🤝 **BALANCED TEAMWORK** - Excellent collaboration! Keep the momentum! 👥"
    fi
}

# Get team members - use partial names for flexible matching
# This allows matching different variations of the same person's git author name
# Laher: matches "Laher Maciel" and "Laher Payot Maciel"
# UnderOfAll: matches Kayki's GitHub username
TEAM_MEMBERS=("Laher" "UnderOfAll")
DISPLAY_NAMES=("Laher Maciel" "Kayki Rocha")

# Create the analytics content
cat > "project_extras/docs/PROJECT_ANALYTICS.md" << EOF
# 📊 Project Analytics Dashboard

<div align="center">

![Analytics](https://img.shields.io/badge/Analytics-Live-brightgreen?style=for-the-badge)
![Team](https://img.shields.io/badge/Team-${#TEAM_MEMBERS[@]}_Members-blue?style=for-the-badge)
![Commits](https://img.shields.io/badge/Commits-$TOTAL_COMMITS-orange?style=for-the-badge)
![Duration](https://img.shields.io/badge/Duration-${PROJECT_DAYS}_Days-purple?style=for-the-badge)

</div>

---

## 📈 Live Project Analytics

*This section is automatically updated when you run \`make\`, \`make fclean\`, or \`make re\`*

$ANALYTICS_SECTION

### 🎯 Weekly Performance

| Developer | This Week | Activity Level | Energy Level | Lines Added | Lines Removed |
|-----------|-----------|----------------|--------------|-------------|---------------|
EOF

# Add weekly performance for each team member
for i in "${!TEAM_MEMBERS[@]}"; do
    member="${TEAM_MEMBERS[$i]}"
    display_name="${DISPLAY_NAMES[$i]}"
    recent=$(get_recent_activity "$member")
    weekly_stats=($(get_weekly_stats "$member"))
    weekly_added=${weekly_stats[0]}
    weekly_removed=${weekly_stats[1]}
    percent=$((recent * 100 / 7))
    
    cat >> "project_extras/docs/PROJECT_ANALYTICS.md" << EOF
| **$display_name** | $recent commits | $(create_weekly_activity_level $weekly_added $weekly_removed) | $(create_emoji_progress $percent) | $weekly_added | $weekly_removed |
EOF
done

cat >> "project_extras/docs/PROJECT_ANALYTICS.md" << EOF

### 🏁 Development Race

| Developer | Commits | Code Changes | Activity Level | Energy Level |
|-----------|---------|--------------|----------------|--------------|
EOF

# Add team members dynamically
for i in "${!TEAM_MEMBERS[@]}"; do
    member="${TEAM_MEMBERS[$i]}"
    display_name="${DISPLAY_NAMES[$i]}"
    commits=$(get_author_commits "$member")
    stats=($(get_author_stats "$member"))
    added=${stats[0]}
    removed=${stats[1]}
    net_changes=$((added - removed))
    total_changes=$((added + removed))
    recent=$(get_recent_activity "$member")
    
    # Calculate percentage based on code changes, not commits
    if [ $TOTAL_ADDED -gt 0 ]; then
        change_percent=$((added * 100 / TOTAL_ADDED))
    else
        change_percent=0
    fi
    
    cat >> "project_extras/docs/PROJECT_ANALYTICS.md" << EOF
| **$display_name** | $commits | +$added/-$removed ($total_changes total) | $(create_activity_level $added $TOTAL_ADDED $removed) | $(create_emoji_progress $change_percent) |
EOF
done

cat >> "project_extras/docs/PROJECT_ANALYTICS.md" << EOF

### 📊 Code Statistics Dashboard

<div align="center">

| Metric | Value | Description |
|--------|-------|-------------|
| **📊 Total Commits** | \`$TOTAL_COMMITS\` | Total number of commits |
| **⏱️ Project Duration** | \`$PROJECT_DAYS days\` | Days since first commit |
| **➕ Lines Added** | \`$TOTAL_ADDED\` | Total lines of code added |
| **➖ Lines Removed** | \`$TOTAL_REMOVED\` | Total lines of code removed |
| **🔄 Net Changes** | \`$NET_CHANGES\` | Net code changes |
| **⚡ Recent Activity** | \`$RECENT_COMMITS commits\` | Commits in last 7 days |

</div>

### 🚀 Development Velocity

<div align="center">

EOF

# Add velocity indicators
if [ $PROJECT_DAYS -gt 0 ]; then
    DAILY_AVERAGE=$((TOTAL_COMMITS / PROJECT_DAYS))
    cat >> "project_extras/docs/PROJECT_ANALYTICS.md" << EOF
| **📅 Average Commits/Day** | \`$DAILY_AVERAGE\` |
| **📈 Development Trend** | $(if [ $DAILY_AVERAGE -gt 5 ]; then echo "🚀 **BLAZING FAST** - You're coding machines!"; elif [ $DAILY_AVERAGE -gt 2 ]; then echo "⚡ **GOOD PACE** - Keep the momentum!"; else echo "🐌 **SLOW BURN** - Time to accelerate!"; fi) |

</div>

EOF
fi

cat >> "project_extras/docs/PROJECT_ANALYTICS.md" << EOF

### 🎮 Current Status

<div align="center">

$(get_motivational_message $RECENT_COMMITS)

</div>

### 🏆 Competition Status

<div align="center">

$(get_competition_message)

</div>

### 📝 Recent Activity

\`\`\`text
$(git log --oneline -10 | sed 's/^/🔹 /')
\`\`\`

### 📁 Most Active Files

\`\`\`text
$(git log --pretty=format: --name-only | sort | uniq -c | sort -rn | head -8 | sed 's/^/📄 /')
\`\`\`

### 🎯 Next Milestones

- [ ] **50 commits** - Halfway to greatness! 🎯
- [ ] **100 commits** - Century club! 💯
- [ ] **Perfect balance** - 50/50 collaboration! ⚖️
- [ ] **Code quality** - Zero norminette errors! ✨
- [ ] **Documentation** - Complete project documentation! 📚

---

<div align="center">

*🔄 Last updated: $(date) | Auto-updated on build*

</div>

<!-- END_ANALYTICS -->

---

## 👥 Team Members

EOF

# Add team members dynamically
for display_name in "${DISPLAY_NAMES[@]}"; do
    cat >> "project_extras/docs/PROJECT_ANALYTICS.md" << EOF
- **$display_name** - Active contributor
EOF
done

cat >> "project_extras/docs/PROJECT_ANALYTICS.md" << EOF

## 🔧 Development Workflow

### Code Review Process
- All changes require pull request review
- Use descriptive commit messages
- Follow 42 norminette standards

### Workload Distribution
- Track individual contributions
- Monitor collaborative efforts
- Ensure balanced development load

## 📊 Project Overview

### Repository Details
- **Language**: C
- **Graphics Library**: MiniLibX
- **Custom Library**: Libft
- **Build System**: Make
- **Code Style**: Norminette compliant

### Development Workflow
1. Create feature branch
2. Implement changes
3. Run \`make norm\` for style check
4. Submit pull request
5. Code review and merge

## 📖 Usage

### Viewing Analytics
- **Main Analytics**: This file contains all project insights
- **Live Updates**: Automatically updated on build/clean operations
- **Individual Stats**: Use \`make personal\` for personal analytics
- **Comparison**: Use \`make compare\` for side-by-side comparison

### Updating Analytics
Analytics are automatically updated when you run:
- \`make\` or \`make all\`
- \`make fclean\`
- \`make re\`

### Manual Updates
To manually update analytics:
\`\`\`bash
./project_extras/scripts/update_analytics.sh
\`\`\`

## 📁 Project Structure

- \`src/\` - Source code
- \`include/\` - Header files
- \`libraries/\` - External libraries
- \`project_extras/\` - Development tools and analytics

## 📋 Final Report

When the project is complete, use \`make final-report\` to generate a comprehensive project summary including:
- Total development time
- Final contribution statistics
- Project completion metrics
- Team collaboration analysis

---

<div align="center">

*This analytics system provides transparent tracking of project development and team collaboration, helping maintain motivation and ensure balanced contributions.*

</div>
EOF

# Exit silently
exit 0