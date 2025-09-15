#!/bin/bash

# Test team detection
get_team_members() {
    local known_team=("Laher Maciel" "Kayki Rocha")
    local team_members=()
    
    # Get all unique authors from git log
    local authors=$(git log --pretty=format:"%an" | sort | uniq)
    echo "Authors found: $authors"
    
    # Check for known team members first
    for member in "${known_team[@]}"; do
        echo "Checking for: $member"
        if echo "$authors" | grep -q "$member"; then
            echo "Found: $member"
            team_members+=("$member")
        else
            echo "Not found: $member"
        fi
    done
    
    echo "Team members: ${team_members[@]}"
    echo "${team_members[@]}"
}

get_team_members

