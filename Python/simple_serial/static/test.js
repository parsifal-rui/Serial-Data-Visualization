let selectedMotor = 'M1'; // Default selected motor

// Function to show or hide views
function showView(viewId) {
    // Hide all views
    const views = document.querySelectorAll('.view');
    views.forEach(view => {
        view.style.display = 'none';
    });

    // Show the selected view
    const selectedView = document.getElementById(viewId);
    if (selectedView) {
        selectedView.style.display = 'block';
    }
}

// Initially display the 'realTimeData' view
showView('realTimeData');

function fetchData() {
    fetch('/data')
        .then(response => response.json())
        .then(data => {
            let time = new Date();
            // Calculate power (Power = Voltage * Current)
            let powerM1 = data.Motor_1.Voltage * data.Motor_1.Current;
            let powerM2 = data.Motor_2.Voltage * data.Motor_2.Current;

            // Depending on the selected motor, display the corresponding data
            if (selectedMotor === 'M1') {
                updateCharts(time, data.Motor_1.Voltage, data.Motor_1.Current, data.Motor_1.Speed, powerM1);
            } else if (selectedMotor === 'M2') {
                updateCharts(time, data.Motor_2.Voltage, data.Motor_2.Current, data.Motor_2.Speed, powerM2);
            }
        })
        .catch(error => {
            console.error('Error fetching data:', error);
            // Optionally display an error message to the user
        });
}

// Event listener for motor selection dropdown
document.getElementById('motorIDs').addEventListener('change', function () {
    selectedMotor = this.value; // Update the selected motor based on user choice
    console.log('Selected Motor:', selectedMotor);
    // Optionally reset charts when motor selection changes
    resetCharts();
});

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
