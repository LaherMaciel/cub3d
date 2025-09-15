# Contributing to Cub3D

This is a collaborative project between two developers. Please follow these guidelines when contributing to the project.

## Getting Started

1. Clone the repository
2. Make your changes directly on main branch
3. Test your changes thoroughly
4. Commit your changes
5. Push to remote repository

## Development Workflow

### Development Approach
- Work directly on the main branch
- Use descriptive commit messages
- Coordinate changes with your collaborator
- Test thoroughly before committing

### Code Style
- Follow the 42 norminette style guide
- Use meaningful variable and function names
- Add comments for complex logic
- Keep functions small and focused

### Testing
- Run `make norm` to check code style
- Test your changes thoroughly before submitting
- Ensure the project builds without errors

## Commit Process

1. Ensure your code follows the style guide
2. Update documentation if needed
3. Test your changes thoroughly
4. Write clear commit messages
5. Push changes to remote repository

## Communication

- Use clear commit messages
- Document any breaking changes
- Discuss major architectural decisions together
- Coordinate changes to avoid conflicts

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

### Rebuilding from scratch
```bash
make re
```

### Preparing for submission
```bash
make submit
```

### Getting help
```bash
make help
```

## Questions?

If you have any questions about the project or need help, don't hesitate to ask your collaborator!
