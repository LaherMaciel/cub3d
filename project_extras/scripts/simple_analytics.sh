#!/bin/bash

# Simple analytics script that just creates the PROJECT_ANALYTICS.md file

TEMP_README="ANALYTICS_TEMP.md"
ANALYTICS_SECTION="<!-- PROJECT_ANALYTICS -->"

# Check if we're in a git repository
if [ ! -d ".git" ]; then
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
    local recent_commits=$1
    
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

# Create the analytics content
cat > "project_extras/docs/PROJECT_ANALYTICS.md" << EOF
# Project Analytics

This document provides comprehensive insights into project development progress and team collaboration patterns for the Cub3D project.

## 📊 Live Analytics

*Note: This section is automatically updated when you run \`make\`, \`make fclean\`, or \`make re\`*

$ANALYTICS_SECTION
## 📊 Live Project Analytics

### 🏁 Development Race
| Developer | Commits | Percentage | Progress Bar | Energy Level |
|-----------|---------|------------|--------------|--------------|
| **Laher Maciel** | $LAHER_COMMITS | $LAHER_PERCENT% | $(create_progress_bar $LAHER_PERCENT) | $(create_emoji_progress $LAHER_PERCENT) |
| **Kayki Rocha** | $KAYKI_COMMITS | $KAYKI_PERCENT% | $(create_progress_bar $KAYKI_PERCENT) | $(create_emoji_progress $KAYKI_PERCENT) |
| **🤝 Collaborative** | $BOTH_COMMITS | $BOTH_PERCENT% | $(create_progress_bar $BOTH_PERCENT) | $(create_emoji_progress $BOTH_PERCENT) |

### 📈 Code Statistics Dashboard
- **📊 Total Commits**: \`$TOTAL_COMMITS\`
- **⏱️ Project Duration**: \`$PROJECT_DAYS days\`
- **➕ Lines Added**: \`$TOTAL_ADDED\`
- **➖ Lines Removed**: \`$TOTAL_REMOVED\`
- **🔄 Net Changes**: \`$NET_CHANGES\`
- **⚡ Recent Activity**: \`$RECENT_COMMITS commits\` (last 7 days)

### 🎯 Weekly Performance
| Developer | This Week | Energy Level |
|-----------|-----------|--------------|
| **Laher** | $(git log --since="7 days ago" --author="Laher" --oneline 2>/dev/null | wc -l) commits | $(create_emoji_progress $(( $(git log --since="7 days ago" --author="Laher" --oneline 2>/dev/null | wc -l) * 100 / 7 ))) |
| **Kayki** | $(git log --since="7 days ago" --author="Kayki" --oneline 2>/dev/null | wc -l) commits | $(create_emoji_progress $(( $(git log --since="7 days ago" --author="Kayki" --oneline 2>/dev/null | wc -l) * 100 / 7 ))) |

### 🚀 Development Velocity
EOF

# Add velocity indicators
if [ $PROJECT_DAYS -gt 0 ]; then
    DAILY_AVERAGE=$((TOTAL_COMMITS / PROJECT_DAYS))
    echo "- **📅 Average Commits/Day**: \`$DAILY_AVERAGE\`" >> "project_extras/docs/PROJECT_ANALYTICS.md"
    
    if [ $DAILY_AVERAGE -gt 5 ]; then
        echo "- **🔥 Velocity Status**: **BLAZING FAST** - You're coding machines!" >> "project_extras/docs/PROJECT_ANALYTICS.md"
    elif [ $DAILY_AVERAGE -gt 2 ]; then
        echo "- **⚡ Velocity Status**: **GOOD PACE** - Keep the momentum!" >> "project_extras/docs/PROJECT_ANALYTICS.md"
    else
        echo "- **🐌 Velocity Status**: **SLOW BURN** - Time to accelerate!" >> "project_extras/docs/PROJECT_ANALYTICS.md"
    fi
fi

# Add motivational sections
cat >> "project_extras/docs/PROJECT_ANALYTICS.md" << EOF

### 🎮 Current Status
$(get_motivational_message $RECENT_COMMITS)

### 🏆 Competition Status
$(get_competition_message $LAHER_COMMITS $KAYKI_COMMITS)

#### 📝 Recent Activity
\`\`\`
$(git log --oneline -8 | sed 's/^/🔹 /')
\`\`\`

#### 📁 Most Active Files
\`\`\`
$(git log --pretty=format: --name-only | sort | uniq -c | sort -rn | head -5 | sed 's/^/📄 /')
\`\`\`

#### 🎯 Next Milestones
- [ ] **50 commits** - Halfway to greatness! 🎯
- [ ] **100 commits** - Century club! 💯
- [ ] **Perfect balance** - 50/50 collaboration! ⚖️
- [ ] **Code quality** - Zero norminette errors! ✨

---
*🔄 Last updated: $(date) | Auto-updated on build*

<!-- END_ANALYTICS -->

## Team Members

- **Laher Maciel** ([@LaherMaciel](https://github.com/LaherMaciel))
- **Kayki Rocha** ([@UnderOfAll](https://github.com/UnderOfAll))

## Development Insights

### 1. GitHub Analytics
- Repository → Insights → Contributors
- View development patterns and collaboration metrics
- Track project evolution over time

### 2. Development Tags
Use prefixes to identify development areas:
- \`[Laher]\` - Laher's development work
- \`[Kayki]\` - Kayki's development work
- \`[Both]\` - Collaborative work

### 3. Code Review Process
- All changes require pull request review
- Use descriptive commit messages
- Follow 42 norminette standards

### 4. Workload Distribution
- Track individual contributions
- Monitor collaborative efforts
- Ensure balanced development load

## Project Statistics

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

## Analytics Features

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

## Usage

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

## Project Management

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

## Final Report

When the project is complete, use \`make final-report\` to generate a comprehensive project summary including:
- Total development time
- Final contribution statistics
- Project completion metrics
- Team collaboration analysis

---

*This analytics system provides transparent tracking of project development and team collaboration, helping maintain motivation and ensure balanced contributions.*
EOF

# Exit silently
exit 0
