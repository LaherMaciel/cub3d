# Project Analytics

This document provides insights into project development progress and team collaboration patterns.

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
- `[Laher]` - Laher's development work
- `[Kayki]` - Kayki's development work
- `[Both]` - Collaborative development

Example:
```
[Laher] Add raycasting algorithm
[Kayki] Implement texture mapping
[Both] Fix memory leaks in map parsing
```

### 3. Development Labels
Use labels to categorize development work:
- `laher-dev` - Development by Laher
- `kayki-dev` - Development by Kayki
- `collaborative` - Joint development
- `review-needed` - Needs peer review

## Workload Distribution

### Phase 1: Project Setup (Target: 50/50)
- [ ] Repository setup
- [ ] Makefile configuration
- [ ] Basic project structure
- [ ] Documentation

### Phase 2: Core Engine (Target: 50/50)
- [ ] Raycasting algorithm
- [ ] Player movement
- [ ] Collision detection
- [ ] Map parsing

### Phase 3: Graphics (Target: 50/50)
- [ ] Texture loading
- [ ] Sprite rendering
- [ ] Color management
- [ ] MiniLibX integration

### Phase 4: Gameplay (Target: 50/50)
- [ ] Input handling
- [ ] Game loop
- [ ] State management
- [ ] Error handling

### Phase 5: Polish (Target: 50/50)
- [ ] Code optimization
- [ ] Memory management
- [ ] Testing
- [ ] Final documentation

## Weekly Check-ins

Every week, review:
1. Commit count per person
2. Lines of code added/removed
3. Number of pull requests created/reviewed
4. Issues assigned and resolved

## GitHub Features for Tracking

### 1. Enable Insights
- Repository Settings → General → Features
- Enable "Issues" and "Pull requests"
- Enable "Discussions" (optional)

### 2. Use Project Boards
- Create project boards for different phases
- Assign tasks to specific members
- Track progress visually

### 3. Use Milestones
- Create milestones for each phase
- Assign issues and PRs to milestones
- Track completion percentage

### 4. Regular Reviews
- Weekly contribution reviews
- Monthly workload assessment
- Adjust distribution if needed

## Fair Collaboration Guidelines

1. **Equal Participation**: Aim for 50/50 contribution split
2. **Regular Communication**: Daily standups or check-ins
3. **Code Reviews**: All code must be reviewed by the other member
4. **Documentation**: Both members should understand all parts
5. **Knowledge Sharing**: Explain complex implementations to each other

## Tools for Tracking

### GitHub CLI (Optional)
```bash
# Install GitHub CLI
curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null
sudo apt update
sudo apt install gh

# View contribution stats
gh api repos/:owner/:repo/stats/contributors
```

### Git Shortlog (Local)
```bash
# View commit count per author
git shortlog -sn

# View commits by author with details
git log --pretty=format:"%h %an %s" --graph
```

## Final Project Report

At the end of the project, use this section to generate a comprehensive development report:

### Overall Development Statistics
```bash
# Generate final project report
make final-report
```

### Key Metrics to Track
- **Total Commits**: Overall commit count per developer
- **Lines of Code**: Total additions, deletions, and net changes
- **Pull Requests**: Created, reviewed, and merged
- **Issues**: Created, assigned, and resolved
- **File Contributions**: Which files were primarily developed by whom
- **Time Investment**: Estimated development time per phase

### Development Areas Breakdown
- **Core Engine**: Raycasting, player movement, collision detection
- **Graphics**: Texture loading, rendering, MiniLibX integration
- **Gameplay**: Input handling, game loop, state management
- **Infrastructure**: Build system, documentation, testing
- **Bug Fixes**: Issue resolution and code optimization

### Collaboration Analysis
- **Code Review Patterns**: Who reviewed what
- **Pair Programming Sessions**: Joint development sessions
- **Knowledge Sharing**: Areas where knowledge was transferred
- **Problem Solving**: How challenges were tackled together

### Project Success Metrics
- **Code Quality**: Norminette compliance, code organization
- **Documentation**: Completeness and clarity
- **Testing**: Coverage and reliability
- **Performance**: Optimization and efficiency
- **Learning Outcomes**: Skills developed and knowledge gained

## Notes

- This analytics system helps understand project development patterns
- The goal is to ensure balanced collaboration and learning
- Adjust development approaches based on insights gained
- Focus on building great software together!
