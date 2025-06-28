# Seed Finder 🌱

A powerful web application for finding Minecraft seeds with specific biome distributions and spawn conditions within a configurable block radius.

## 🎯 Overview

Seed Finder is a complete web application that helps Minecraft players discover optimal seeds for their worlds. It combines high-performance C++ biome generation algorithms with a modern web interface to provide fast, accurate seed searching capabilities.

## ✨ Features

- **Biome Analysis**: Scan seeds to find worlds with diverse biome distributions
- **Custom Spawn Search**: Find seeds with specific biome spawns (e.g., Ice Spikes, Jungle, Badlands)
- **Multi-Version Support**: Compatible with Minecraft 1.18 and 1.19
- **High Performance**: C++ backend using cubiomes library for fast biome generation
- **Modern Web Interface**: Built with Nuxt.js and Tailwind CSS
- **RESTful API**: Django backend with comprehensive seed data endpoints
- **Real-time Results**: Get seed information with biome details and spawn coordinates

## 🏗️ Architecture

The project consists of three main components:

### 1. C++ Implementation (`new_cpp_implementation/`)
- **Core Algorithm**: High-performance biome generation using the cubiomes library
- **World Scanner**: Multi-threaded seed scanning with configurable parameters
- **Shared Library**: Python-compatible shared objects for web integration
- **Version Support**: Minecraft 1.18 and 1.19 biome generation

### 2. Web Backend (`web/server/`)
- **Django REST API**: RESTful endpoints for seed data
- **Database**: SQLite storage for seed collections and version management
- **C Integration**: Direct integration with C++ shared libraries
- **Admin Interface**: Django admin for managing seed data

### 3. Web Frontend (`web/client/`)
- **Nuxt.js 3**: Modern Vue.js framework with SSR capabilities
- **Tailwind CSS**: Utility-first CSS framework for responsive design
- **Interactive UI**: Real-time search, version selection, and biome filtering
- **Mobile Responsive**: Optimized for desktop and mobile devices

## 🚀 Quick Start

### Prerequisites

- **C++ Compiler**: GCC with C++11 support
- **Python 3.8+**: For Django backend
- **Node.js 16+**: For Nuxt.js frontend
- **Make**: For building C++ components

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/seed_finder.git
   cd seed_finder
   ```

2. **Build C++ Components**
   ```bash
   cd new_cpp_implementation
   make
   cd ..
   ```

3. **Setup Backend**
   ```bash
   cd web/server
   pip install -r requirements.txt
   python manage.py migrate
   python manage.py runserver
   ```

4. **Setup Frontend**
   ```bash
   cd web/client
   npm install
   npm run dev
   ```

5. **Access the Application**
   - Frontend: http://localhost:3000
   - Backend API: http://localhost:8000

## 📖 Usage

### Finding Better Seeds
1. Select your Minecraft version (1.18 or 1.19)
2. Click "Get Seeds" to find worlds with diverse biome distributions
3. View seed details including spawn coordinates and biome information

### Custom Spawn Search
1. Use the search bar to find specific biomes (e.g., "ice spikes", "jungle")
2. Click "Search" to find seeds with that biome at spawn
3. Browse favorite picks for popular spawn types

### Biome ID Lookup
1. Navigate to the "Find biome id" section
2. Search for any Minecraft biome to get its ID
3. Use biome IDs for advanced seed searching

## 🔧 API Endpoints

### Get Better Seeds
```http
POST /api/better-seeds/
Content-Type: application/json

{
  "version": 1.18
}
```

### Get Seed Information
```http
POST /api/seed-info/{seed}/
Content-Type: application/json

{
  "version": 1.18
}
```

### Get Custom Seeds
```http
POST /api/custom-seeds/
Content-Type: application/json

{
  "version": 1.18,
  "biome_id": 140
}
```

## 🛠️ Development

### Project Structure
```
seed_finder/
├── new_cpp_implementation/     # C++ core algorithms
│   ├── world.cpp              # World generation logic
│   ├── scanner.cpp            # Seed scanning algorithms
│   └── shared_python.c        # Python integration
├── web/
│   ├── server/                # Django backend
│   │   ├── apis/             # REST API endpoints
│   │   └── requirements.txt   # Python dependencies
│   └── client/               # Nuxt.js frontend
│       ├── pages/            # Vue.js pages
│       ├── components/       # Reusable components
│       └── package.json      # Node.js dependencies
├── cubiomes/                 # Minecraft biome generation library
└── README.md                # This file
```

### Building from Source
```bash
# Build C++ components
cd new_cpp_implementation
make clean && make

# Create shared library
cd ..
./create_shared_file.sh
```

### Adding New Features
1. **New Biome Types**: Update `world.cpp` and `scanner.cpp`
2. **API Endpoints**: Add views in `web/server/apis/views.py`
3. **Frontend Components**: Create Vue components in `web/client/components/`

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Development Guidelines
- Follow C++11 standards for backend code
- Use TypeScript for frontend development
- Maintain API documentation
- Add tests for new features
- Follow PEP 8 for Python code


## 🙏 Acknowledgments

- **Cubiomes Library**: Minecraft biome generation algorithms
- **Nuxt.js**: Modern Vue.js framework
- **Django**: Python web framework
- **Tailwind CSS**: Utility-first CSS framework

## 📞 Support

- **Issues**: Report bugs and feature requests on GitHub
- **Discussions**: Join community discussions for help and ideas
- **Documentation**: Check the wiki for detailed guides

---

**Happy Seed Hunting! 🌍**
