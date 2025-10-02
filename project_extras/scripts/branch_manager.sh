#!/bin/bash

# Branch Management Script for Cub3D Project
# This script helps manage the branch naming convention

echo "🌿 Cub3D Branch Manager"
echo "======================"

# Function to create a new branch
create_branch() {
    local type=$1
    local description=$2
    local branch_name="${type}/${description}"
    
    if git show-ref --verify --quiet refs/heads/"$branch_name"; then
        echo "❌ Branch '$branch_name' already exists!"
        return 1
    fi
    
    git checkout -b "$branch_name"
    echo "✅ Created branch: $branch_name"
}

# Function to list all branches
list_branches() {
    echo "📋 Available Branches:"
    echo "---------------------"
    git branch | grep -v "^\*" | sed 's/^  /🌿 /'
    echo ""
    echo "Current branch: $(git branch --show-current)"
}

# Function to switch to a branch
switch_branch() {
    local branch_name=$1
    if git show-ref --verify --quiet refs/heads/"$branch_name"; then
        git checkout "$branch_name"
        echo "✅ Switched to: $branch_name"
    else
        echo "❌ Branch '$branch_name' does not exist!"
        echo "Available branches:"
        git branch | grep -v "^\*" | sed 's/^  /  - /'
    fi
}

# Function to delete a branch
delete_branch() {
    local branch_name=$1
    if [ "$branch_name" = "master" ]; then
        echo "❌ Cannot delete master branch!"
        return 1
    fi
    
    if git show-ref --verify --quiet refs/heads/"$branch_name"; then
        git branch -d "$branch_name"
        echo "✅ Deleted branch: $branch_name"
    else
        echo "❌ Branch '$branch_name' does not exist!"
    fi
}

# Function to show branch naming convention
show_convention() {
    echo "📖 Branch Naming Convention:"
    echo "==========================="
    echo "🌿 feature/description  - New features (e.g., feature/raycasting-engine)"
    echo "🔧 fix/description      - Bug fixes (e.g., fix/memory-leaks)"
    echo "♻️  refactor/description - Code refactoring (e.g., refactor/optimize-rendering)"
    echo "📚 docs/description     - Documentation (e.g., docs/update-readme)"
    echo ""
}

# Main menu
case "$1" in
    "list"|"ls")
        list_branches
        ;;
    "create"|"new")
        if [ -z "$2" ] || [ -z "$3" ]; then
            echo "Usage: $0 create <type> <description>"
            echo "Types: feature, fix, refactor, docs"
            echo "Example: $0 create feature player-movement"
            exit 1
        fi
        create_branch "$2" "$3"
        ;;
    "switch"|"checkout")
        if [ -z "$2" ]; then
            echo "Usage: $0 switch <branch-name>"
            echo "Example: $0 switch feature/raycasting-engine"
            exit 1
        fi
        switch_branch "$2"
        ;;
    "delete"|"rm")
        if [ -z "$2" ]; then
            echo "Usage: $0 delete <branch-name>"
            echo "Example: $0 delete feature/raycasting-engine"
            exit 1
        fi
        delete_branch "$2"
        ;;
    "convention"|"help")
        show_convention
        ;;
    *)
        echo "🌿 Cub3D Branch Manager"
        echo "======================"
        echo ""
        echo "Usage: $0 <command> [options]"
        echo ""
        echo "Commands:"
        echo "  list, ls                    - List all branches"
        echo "  create, new <type> <desc>   - Create new branch"
        echo "  switch, checkout <name>     - Switch to branch"
        echo "  delete, rm <name>           - Delete branch"
        echo "  convention, help            - Show naming convention"
        echo ""
        echo "Examples:"
        echo "  $0 list"
        echo "  $0 create feature texture-system"
        echo "  $0 switch feature/raycasting-engine"
        echo "  $0 delete feature/old-feature"
        echo "  $0 convention"
        ;;
esac

