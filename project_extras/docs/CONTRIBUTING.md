# Contributing to Cub3D

This is a collaborative project between two developers. Please follow these guidelines when contributing to the project.

## Getting Started

1. Clone the repository
2. Create a new branch for your feature/fix
3. Make your changes
4. Test your changes thoroughly
5. Submit a pull request

## Development Workflow

### Branch Naming Convention
- `feature` - New functionality and feature implementation
- `fix` - Bug fixes and issue resolution
- `refactor` - Code optimization and structural improvements
- `docs` - Documentation updates and project guides

### Code Style
- Follow the 42 norminette style guide
- Use meaningful variable and function names
- Add comments for complex logic
- Keep functions small and focused

### Testing
- Run `make norm` to check code style
- Test your changes thoroughly before submitting
- Ensure the project builds without errors

## Pull Request Process

1. Ensure your code follows the style guide
2. Update documentation if needed
3. Add tests if applicable
4. Request review from your collaborator
5. Address any feedback before merging

## Communication

- Use clear commit messages
- Document any breaking changes
- Discuss major architectural decisions together
- Keep the project board updated

## File Structure

```
cub3d/
├── src/                 # Main source files
├── include/             # Header files
├── libraries/           # External libraries
│   ├── libft/          # Custom library
│   └── minilibx-linux/ # Graphics library
├── objects/            # Compiled objects
└── maps/               # Map files
```

## Common Tasks

### Building the project
```bash
make
```

### Running norminette
```bash
make norm
```

### Cleaning build files
```bash
make clean
```

### Full clean
```bash
make fclean
```

## Questions?

If you have any questions about the project or need help, don't hesitate to ask your collaborator!
