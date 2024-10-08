// Function to show the desired view
function showView(viewId) {
  let views = document.getElementsByClassName('view');
  for (let view of views) {
      view.style.display = 'none';
  }
  document.getElementById(viewId).style.display = 'block';
}
// Initialize charts
let allMotorsVoltageChart = new Chart(
  document.getElementById('allMotorsVoltageChart').getContext('2d'),
  {
    type: 'bar',
    data: {
      labels: [],
      datasets: [],
    },
    options: {
      // Chart options
    },
  }
);

let allMotorsCurrentChart = new Chart(
  document.getElementById('allMotorsCurrentChart').getContext('2d'),
  {
    type: 'bar',
    data: {
      labels: [],
      datasets: [],
    },
    options: {
      // Chart options
    },
  }
);

let allMotorsSpeedChart = new Chart(
  document.getElementById('allMotorsSpeedChart').getContext('2d'),
  {
    type: 'bar',
    data: {
      labels: [],
      datasets: [],
    },
    options: {
      // Chart options
    },
  }
);

// Function to update all motors' charts
function updateAllMotorsCharts(time, motorData) {
  updateChartDatasets(allMotorsVoltageChart, time, motorData, 'Voltage');
  updateChartDatasets(allMotorsCurrentChart, time, motorData, 'Current');
  updateChartDatasets(allMotorsSpeedChart, time, motorData, 'Speed');
}

// Function to update datasets for a chart
function updateChartDatasets(chart, time, motorData, parameter) {
  chart.data.labels = []; // 清空时间标签
  chart.data.datasets = []; // 清空所有数据集
  if (!chart) {
    console.error(`Chart for ${parameter} is undefined.`);
    return;
  }

  Object.keys(motorData).forEach((motorId) => {
    const motor = motorData[motorId];
    const value = motor[parameter];

    // Find or create dataset for the motor
    let dataset = chart.data.datasets.find((ds) => ds.label === motorId);

    if (!dataset) {
      const color = getRandomColor();
      dataset = {
        label: motorId,
        data: [],
        borderColor: color,
        backgroundColor: color,
        fill: false,
      };
      chart.data.datasets.push(dataset);
    }

    // Add new data point
    dataset.data.push({ x: time, y: value });

    // Keep only the last 10 data points
    if (dataset.data.length > 10) {
      dataset.data.shift();
    }
  });

  chart.update();
}

// Function to get a random color
function getRandomColor() {
  // Implementation...
}

// Fetch data and update charts
function fetchData() {
  fetch('/data')
    .then((response) => response.json())
    .then((data) => {
      let time = new Date();
      updateAllMotorsCharts(time, data);
    })
    .catch((error) => {
      console.error('Error fetching data:', error);
    });
}

// Start fetching data at intervals
setInterval(fetchData, 2000);
