
# European Options Monte Carlo Simulation Library

## Overview
This C++ library is specialized for Monte Carlo simulations in quantitative finance, particularly for European options. It integrates sophisticated software architecture with real-time data processing and statistical analysis to enhance simulation accuracy. Utilizing modern C++ practices and object-oriented design, the library supports intricate financial modeling for European options and facilitates data visualization via Python's Matplotlib.

## Features
- **Monte Carlo Simulations**: Efficient simulation of European option pricing.
- **Real-Time Data Processing**: Capability to process live data for timely simulations.
- **Statistical Analysis**: Robust analytical methods for reliable simulation outcomes.
- **Object-Oriented Design**: Modular and maintainable code using contemporary C++ approaches.
- **Data Visualization**: Integration with Python Matplotlib for graphical data representation.

## Code Structure
The library comprises several components, each serving a specific role:
- **Core Simulation and Analysis**: 
  - `EuropeanOptionMC.h`: Central class for Monte Carlo simulations of European options.
  - `StockPriceSimulator.h`: Simulates stock price paths using stochastic processes.
  - `ConvergenceTable.h`: Manages and analyzes the convergence of simulation results.
  - `StatisticsMC.h`, `StatisticsMean.h`: Provides statistical analysis tools for Monte Carlo methods.
- **Financial Data Handling**:
  - `FinancialDataCollector.h`, `FinancialDataAnalyzer.h`: Collects and analyzes financial data.
  - `HistoricalMeanReturnCalculator.h`, `HistoricalVolatilityCalculator.h`, `HistoricalMomentumCalculator.h`: Calculate historical financial metrics.
- **Random Number Generation**:
  - `RandomBase.h`, `RandomParkMiller.h`, `AntiThetic.h`: Base and specific implementations of random number generators.
- **Utility and Support**:
  - `Payoff.h`, `VanillaOption.h`: Represents payoffs and options in financial contexts.
  - `UtilityFunctions.h`, `CommonUtilities.h`: General utility functions for various tasks.
  - `PythonMatplotlibGenerator.h`: Generates scripts for data plotting using Matplotlib.
- **Parameter Handling**:
  - `ParameterInner.h`, `Parameters.h`, `ParametersConstant.h`: Handles various simulation parameters.

## Getting Started
### Prerequisites
- C++ Compiler (C++11 or later)
- Python 3.x with Matplotlib installed

### Usage
Include the necessary headers in your project and utilize the classes and functions as required for simulation and analysis.

## Licenses
This project is licensed under the MIT License - see the [LICENSE.txt](./LICENSE.txt) file for details.

Parts of this library are adapted from code by Mark Joshi (author of "C++ Design Patterns and Derivatives Pricing"), which is licensed as follows:
```
Copyright (c) 2002
Mark Joshi

Permission to use, copy, modify, distribute and sell this
software for any purpose is hereby
granted without fee, provided that the above copyright notice
appear in all copies and that both that copyright notice and
this permission notice appear in supporting documentation.
Mark Joshi makes no representations about the
suitability of this software for any purpose. It is provided
"as is" without express or implied warranty.
```
Users of this library must comply with the licensing terms of both the MIT License and Mark Joshi's license where applicable.

## Acknowledgments
- Special thanks to Mark Joshi for his foundational work in the field of quantitative finance.
