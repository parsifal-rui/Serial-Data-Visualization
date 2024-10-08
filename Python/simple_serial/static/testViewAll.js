
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
      plugins: {
        annotation: {
          annotations: {
            voltageLine: {
              type: 'line',
              yMin: 0,
              yMax: 0,
              borderColor: 'red',
              borderWidth: 2,
              label: {
                enabled: true,
                content: 'Voltage Reference',
                position: 'end'
              }
            }
          }
        }
      },
      scales: {
        x: { stacked: true },
        y: { beginAtZero: true, stacked: true }
      }
    }
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
      plugins: {
        annotation: {
          annotations: {
            currentLine: {
              type: 'line',
              yMin: 0,
              yMax: 0,
              borderColor: 'blue',
              borderWidth: 2,
              label: {
                enabled: true,
                content: 'Current Reference',
                position: 'end'
              }
            }
          }
        }
      },
      scales: {
        x: { stacked: true },
        y: { beginAtZero: true, stacked: true }
      }
    }
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
      plugins: {
        annotation: {
          annotations: {
            speedLine: {
              type: 'line',
              yMin: 0,
              yMax: 0,
              borderColor: 'green',
              borderWidth: 2,
              label: {
                enabled: true,
                content: 'Speed Reference',
                position: 'end'
              }
            }
          }
        }
      },
      scales: {
        x: { stacked: true },
        y: { beginAtZero: true, stacked: true }
      }
    }
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
  const letters = '0123456789ABCDEF';
  let color = '#';
  for (let i = 0; i < 6; i++) {
    color += letters[Math.floor(Math.random() * 16)];
  }
  return color;
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
// Function to set reference line based on input value
// Function to set reference line based on input value
function setReference(type) {
  const voltageRefValue = parseFloat(document.getElementById('voltageRef').value); // 确保输入的数值为浮点数
  const currentRefValue = parseFloat(document.getElementById('currentRef').value);
  const speedRefValue = parseFloat(document.getElementById('speedRef').value);

  // 为电压设置参考线
  if (type === 'voltage' && !isNaN(voltageRefValue)) {  // 确保值不为空且为有效数字
    allMotorsVoltageChart.options.plugins.annotation.annotations.voltageLine.yMin = voltageRefValue;
    allMotorsVoltageChart.options.plugins.annotation.annotations.voltageLine.yMax = voltageRefValue;
    allMotorsVoltageChart.update();
  }
  
  // 为电流设置参考线
  else if (type === 'current' && !isNaN(currentRefValue)) {
    allMotorsCurrentChart.options.plugins.annotation.annotations.currentLine.yMin = currentRefValue;
    allMotorsCurrentChart.options.plugins.annotation.annotations.currentLine.yMax = currentRefValue;
    allMotorsCurrentChart.update();
  }

  // 为速度设置参考线
  else if (type === 'speed' && !isNaN(speedRefValue)) {
    allMotorsSpeedChart.options.plugins.annotation.annotations.speedLine.yMin = speedRefValue;
    allMotorsSpeedChart.options.plugins.annotation.annotations.speedLine.yMax = speedRefValue;
    allMotorsSpeedChart.update();
  }
}

// Start fetching data at intervals
setInterval(fetchData, 2000);
