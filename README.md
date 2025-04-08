# React Task Management Application

A modern task management application built with React and Vite, featuring a drag-and-drop interface and a clean, responsive design.

## Features

- Modern React-based frontend with Vite
- Drag and drop functionality for task management
- Responsive design using Bootstrap 5
- React Router for navigation
- Clean and intuitive user interface

## Tech Stack

### Frontend
- React 19
- Vite 6
- Bootstrap 5
- React DnD (Drag and Drop)
- Font Awesome
- React Router DOM

### Development Tools
- ESLint
- TypeScript support
- Vite development server

## Project Structure

```
├── vite-project/          # Frontend React application
│   ├── src/              # Source files
│   ├── public/           # Static assets
│   └── package.json      # Frontend dependencies
├── backend/              # Backend server
└── uploads/             # File uploads directory
```

## Getting Started

### Prerequisites

- Node.js (Latest LTS version recommended)
- npm or yarn package manager

### Installation

1. Clone the repository
2. Navigate to the frontend directory:
   ```bash
   cd vite-project
   ```
3. Install dependencies:
   ```bash
   npm install
   ```

### Development

To start the development server:

```bash
npm run dev
```

The application will be available at `http://localhost:5173`

### Building for Production

To create a production build:

```bash
npm run build
```

To preview the production build:

```bash
npm run preview
```

## Available Scripts

- `npm run dev` - Start development server
- `npm run build` - Create production build
- `npm run lint` - Run ESLint
- `npm run preview` - Preview production build

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request
