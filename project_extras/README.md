# Project Extras

This folder contains all the collaboration and analytics tools for the Cub3D project. These files are **NOT** part of the mandatory submission and should be removed before submitting to 42.

## 📁 Folder Structure

```
project_extras/
├── scripts/                    # Analytics and utility scripts
│   ├── silent_analytics.sh    # Silent README analytics update
│   ├── project_stats.sh       # Project statistics display
│   ├── final_report.sh        # Comprehensive project report
│   └── prepare_submission.sh  # Submission preparation script
├── .github/                    # GitHub workflows and templates
│   ├── workflows/             # CI/CD workflows
│   └── ISSUE_TEMPLATE/        # Issue and PR templates
└── docs/                      # Documentation files
    ├── CONTRIBUTING.md        # Collaboration guidelines
    ├── CODEOWNERS            # Code ownership rules
    └── PROJECT_ANALYTICS.md  # Analytics documentation
```

## 🚀 Usage

### During Development
- All analytics and collaboration features work automatically
- README updates happen on every build/clean
- Use `make stats` or `make final-report` for detailed analytics

### Before Submission
```bash
make submit
```
This will:
- Remove all collaboration files
- Clean README analytics
- Prepare project for submission
- Create backup of extras

### After Submission
To restore collaboration features:
```bash
# Restore from backup (if available)
mv project_extras_backup project_extras

# Or re-clone from GitHub
git clone <your-repo>
```

## 📋 What Gets Removed for Submission

- `project_extras/` folder (entire folder)
- `CONTRIBUTING.md`
- `CODEOWNERS`
- `PROJECT_ANALYTICS.md`
- `.github/` folder
- README analytics section
- Build artifacts

## ✅ What Remains for Submission

- `src/` (source code)
- `include/` (headers)
- `libraries/` (libft, minilibx)
- `Makefile`
- `.gitignore`
- `README.md` (clean version)

## 🔧 Commands

- `make submit` - Prepare for submission
- `make stats` - Show project statistics
- `make final-report` - Generate comprehensive report

## ⚠️ Important Notes

- **Always run `make submit` before submission**
- **Test your project after running submit**
- **Keep this folder for future development**
- **Don't commit submission-ready files to main branch**
