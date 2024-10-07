// Function to show the desired view
function showView(viewId) {
    let views = document.getElementsByClassName('view');
    for (let view of views) {
        view.style.display = 'none';
    }
    document.getElementById(viewId).style.display = 'block';
}

// // Example chart setup (for voltage, current, and speed)
// let voltageCtx = document.getElementById('voltageChart').getContext('2d');
// let currentCtx = document.getElementById('currentChart').getContext('2d');
// let speedCtx = document.getElementById('speedChart').getContext('2d');

// // Create empty charts
// let voltageChart = new Chart(voltageCtx, {
//     type: 'line',
//     data: { labels: [], datasets: [{ label: 'Voltage', data: [] }] },
//     options: { scales: { x: { type: 'linear', position: 'bottom' } } }
// });

// let currentChart = new Chart(currentCtx, {
//     type: 'line',
//     data: { labels: [], datasets: [{ label: 'Current', data: [] }] },
//     options: { scales: { x: { type: 'linear', position: 'bottom' } } }
// });

// let speedChart = new Chart(speedCtx, {
//     type: 'line',
//     data: { labels: [], datasets: [{ label: 'Speed', data: [] }] },
//     options: { scales: { x: { type: 'linear', position: 'bottom' } } }
// });





//js code for real time data

// Global variable to store the selected motor


// // Fetch available serial ports from the server
// function fetchSerialPorts() {
//     fetch('/serial_ports')  // This endpoint will return the available serial ports
//         .then(response => response.json())
//         .then(ports => {
//             const serialPortsDropdown = document.getElementById('serialPorts');
//             // Clear existing options
//             serialPortsDropdown.innerHTML = '';

//             // Populate dropdown with the received ports
//             ports.forEach(port => {
//                 const option = document.createElement('option');
//                 option.value = port;
//                 option.textContent = port;
//                 serialPortsDropdown.appendChild(option);
//             });
//         })
//         .catch(error => {
//             console.error('Error fetching serial ports:', error);
//         });
// }

// // Call fetchSerialPorts when the page loads to populate the dropdown
// window.onload = fetchSerialPorts;

// // Event listener for when a serial port is selected
// document.getElementById('serialPorts').addEventListener('change', function () {
//     const selectedPort = this.value;
//     console.log('Selected Port:', selectedPort);
//     // You can add code here to handle actions based on the selected port.
// });
let selectedMotor = 'M1';  // Default motor is M1
function fetchData() {
    fetch('/data')
        .then(response => response.json())
        .then(data => {
            let time = new Date();
              // Fetch power by calculating it (Power = Voltage * Current)
            let powerM1 = data.Motor_1.Voltage * data.Motor_1.Current;
            let powerM2 = data.Motor_2.Voltage * data.Motor_2.Current;
            // Depending on the selected motor, display the corresponding data
            if (selectedMotor === 'M1') {
                updateTable(time, data.Motor_1.Voltage, data.Motor_1.Current, data.Motor_1.Speed);
                updateCharts(time, data.Motor_1.Voltage, data.Motor_1.Current, data.Motor_1.Speed, powerM1);
            } else if (selectedMotor === 'M2') {
                updateTable(time, data.Motor_2.Voltage, data.Motor_2.Current, data.Motor_2.Speed);
                updateCharts(time, data.Motor_2.Voltage, data.Motor_2.Current, data.Motor_2.Speed, powerM2);
            }
        })
        .catch(error => {
            console.error('Error fetching data:', error);
        });
}

// Event listener for when the user selects a motor from the dropdown
document.getElementById('motorIDs').addEventListener('change', function () {
    selectedMotor = this.value;  // Update the selected motor based on user choice
    console.log('Selected Motor:', selectedMotor);
    // Immediately fetch and display data for the selected motor
    resetCharts();
});


// Function to update the table
function updateTable(time, voltage, current, speed) {
    const tableBody = document.getElementById('realTimeTable');

    // Create a new row for the table
    const row = document.createElement('tr');

    // Create individual cells for time, voltage, current, and speed
    const timeCell = document.createElement('td');
    timeCell.textContent = time;

    const voltageCell = document.createElement('td');
    voltageCell.textContent = voltage.toFixed(2); // Format voltage to 2 decimal places

    const currentCell = document.createElement('td');
    currentCell.textContent = current.toFixed(2); // Format current to 2 decimal places

    const speedCell = document.createElement('td');
    speedCell.textContent = speed;

    // Append the cells to the row
    row.appendChild(timeCell);
    row.appendChild(voltageCell);
    row.appendChild(currentCell);
    row.appendChild(speedCell);

        // Append the row to the table body
        tableBody.appendChild(row);
}

// Function to draw charts
function resetCharts() {
    voltageChart.data.labels = [];
    voltageChart.data.datasets[0].data = [];
    currentChart.data.labels = [];
    currentChart.data.datasets[0].data = [];
    speedChart.data.labels = [];
    speedChart.data.datasets[0].data = [];
    powerChart.data.labels = [];
    powerChart.data.datasets[0].data = [];
}

const chartOptions = {
    type: 'line',
    data: {
        labels: [],
        datasets: [{
            data: [],
            borderColor: '',
            backgroundColor: '',
            fill: false,
            label: ''
        }]
    },
    options: {
        scales: {
            x: {
                type: 'time',
                time: {
                    unit: 'second',
                    tooltipFormat: 'HH:mm:ss'
                },
                ticks: {
                    autoSkip: true,
                    maxTicksLimit: 10
                }
            },
            y: {
                beginAtZero: true
            }
        }
    }
};

// Create Voltage Chart
let voltageChart = new Chart(document.getElementById('voltageChart').getContext('2d'), {
    ...chartOptions,
    data: {
        labels: [],
        datasets: [{
            label: 'Voltage (V)',
            data: [],
            borderColor: 'rgba(255, 99, 132, 1)',
            backgroundColor: 'rgba(255, 99, 132, 0.2)',
            fill: false
        }]
    }
});

// Create Current Chart
let currentChart = new Chart(document.getElementById('currentChart').getContext('2d'), {
    ...chartOptions,
    data: {
        labels: [],
        datasets: [{
            label: 'Current (A)',
            data: [],
            borderColor: 'rgba(54, 162, 235, 1)',
            backgroundColor: 'rgba(54, 162, 235, 0.2)',
            fill: false
        }]
    }
});

// Create Speed Chart
let speedChart = new Chart(document.getElementById('speedChart').getContext('2d'), {
    ...chartOptions,
    data: {
        labels: [],
        datasets: [{
            label: 'Speed (RPM)',
            data: [],
            borderColor: 'rgba(75, 192, 192, 1)',
            backgroundColor: 'rgba(75, 192, 192, 0.2)',
            fill: false
        }]
    }
});

// Create Power Chart
let powerChart = new Chart(document.getElementById('powerChart').getContext('2d'), {
    ...chartOptions,
    data: {
        labels: [],
        datasets: [{
            label: 'Power (W)',
            data: [],
            borderColor: 'rgba(153, 102, 255, 1)',
            backgroundColor: 'rgba(153, 102, 255, 0.2)',
            fill: false
        }]
    }
});

function updateCharts(time, voltage, current, speed, power) {
    updateSingleChart(voltageChart, time, voltage);
    updateSingleChart(currentChart, time, current);
    updateSingleChart(speedChart, time, speed);
    updateSingleChart(powerChart, time, power);
}

function updateSingleChart(chart, time, value) {
    chart.data.labels.push(time);
    chart.data.datasets[0].data.push(value);

    if (chart.data.labels.length > 10) {
        chart.data.labels.shift();
        chart.data.datasets[0].data.shift();
    }
    chart.update();
}


// Poll the server every 2 seconds for new data
setInterval(fetchData, 2000);