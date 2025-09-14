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

# Dynamic teammate detection from git repository
get_team_members() {
    # Define known team members (always include both)
    local known_team=("Laher Maciel" "Kayki Rocha")
    local team_members=()
    
    # Always include known team members
    team_members=("${known_team[@]}")
    
    # Get all unique authors from git log
    local authors=$(git log --pretty=format:"%an" | sort | uniq)
    
    # Add any other authors not in the known team
    while IFS= read -r author; do
        if [ -n "$author" ] && [[ ! " ${team_members[@]} " =~ " ${author} " ]]; then
            team_members+=("$author")
        fi
    done <<< "$authors"
    
    echo "${team_members[@]}"
}

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

# Create professional progress bars
create_progress_bar() {
    local percent=$1
    local width=25
    local filled=$((percent * width / 100))
    local empty=$((width - filled))
    
    printf "┌"
    for i in $(seq 1 $width); do printf "─"; done
    printf "┐\n│"
    for i in $(seq 1 $filled); do printf "█"; done
    for i in $(seq 1 $empty); do printf "░"; done
    printf "│ %3d%%\n└" $percent
    for i in $(seq 1 $width); do printf "─"; done
    printf "┘"
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

# Generate professional competition message
get_competition_message() {
    local team_members=("$@")
    local max_commits=0
    local leader=""
    local total_commits=0
    
    # Find the leader
    for member in "${team_members[@]}"; do
        local commits=$(get_author_commits "$member")
        total_commits=$((total_commits + commits))
        if [ "$commits" -gt "$max_commits" ]; then
            max_commits=$commits
            leader="$member"
        fi
    done
    
    if [ ${#team_members[@]} -eq 1 ]; then
        echo "👤 **SOLO DEVELOPER** - You're handling this project independently! Great work!"
    elif [ "$max_commits" -gt "$((total_commits / 2))" ]; then
        echo "🏆 **$leader is LEADING** - Strong performance! Others, time to step up! 🎯"
    else
        echo "🤝 **BALANCED TEAMWORK** - Excellent collaboration! Keep the momentum! 👥"
    fi
}

# Get team members dynamically - always include both team members
TEAM_MEMBERS=("Laher Maciel" "Kayki Rocha")

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

### 🏁 Development Race

| Developer | Commits | Percentage | Progress Bar | Energy Level |
|-----------|---------|------------|--------------|--------------|
EOF

# Add team members dynamically
for member in "${TEAM_MEMBERS[@]}"; do
    commits=$(get_author_commits "$member")
    percent=$((commits * 100 / TOTAL_COMMITS))
    stats=($(get_author_stats "$member"))
    added=${stats[0]}
    removed=${stats[1]}
    recent=$(get_recent_activity "$member")
    
    cat >> "project_extras/docs/PROJECT_ANALYTICS.md" << EOF
| **$member** | $commits | $percent% | $(create_progress_bar $percent) | $(create_emoji_progress $percent) |
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

### 🎯 Weekly Performance

| Developer | This Week | Energy Level | Lines Added | Lines Removed |
|-----------|-----------|--------------|-------------|---------------|
EOF

# Add weekly performance for each team member
for member in "${TEAM_MEMBERS[@]}"; do
    recent=$(get_recent_activity "$member")
    stats=($(get_author_stats "$member"))
    added=${stats[0]}
    removed=${stats[1]}
    percent=$((recent * 100 / 7))
    
    cat >> "project_extras/docs/PROJECT_ANALYTICS.md" << EOF
| **$member** | $recent commits | $(create_emoji_progress $percent) | $added | $removed |
EOF
done

cat >> "project_extras/docs/PROJECT_ANALYTICS.md" << EOF

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

$(get_competition_message "${TEAM_MEMBERS[@]}")

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
for member in "${TEAM_MEMBERS[@]}"; do
    cat >> "project_extras/docs/PROJECT_ANALYTICS.md" << EOF
- **$member** - Active contributor
EOF
done

cat >> "project_extras/docs/PROJECT_ANALYTICS.md" << EOF

## 🔧 Development Insights

### 1. GitHub Analytics
- Repository → Insights → Contributors
- View development patterns and collaboration metrics
- Track project evolution over time

### 2. Development Tags
Use prefixes to identify development areas:
- \`[AuthorName]\` - Specific author's development work
- \`[Both]\` - Collaborative work

### 3. Code Review Process
- All changes require pull request review
- Use descriptive commit messages
- Follow 42 norminette standards

### 4. Workload Distribution
- Track individual contributions
- Monitor collaborative efforts
- Ensure balanced development load

## 📊 Project Statistics

### Repository Overview
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

## 🚀 Analytics Features

### Real-time Tracking
- Live commit statistics
- Development velocity
- Code contribution metrics
- Team performance insights

### Historical Analysis
- Project timeline
- Development patterns
- Collaboration trends
- Milestone tracking

### Competitive Elements
- Development race tracking
- Energy level indicators
- Performance comparisons
- Motivation metrics

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

## 📁 Project Management

### File Organization
- \`src/\` - Source code
- \`include/\` - Header files
- \`libraries/\` - External libraries
- \`project_extras/\` - Development tools and analytics

### Collaboration Tools
- GitHub Issues for bug tracking
- Pull Requests for code review
- Project boards for task management
- Analytics for progress tracking

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