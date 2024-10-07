// 创建图表
function createChart(ctx, label) {
    return new Chart(ctx, {
        type: 'line',
        data: {
            labels: [],
            datasets: [{
                label: label,
                data: [],
                borderColor: 'rgb(75, 192, 192)',
                tension: 0.1
            }]
        },
        options: {
            responsive: true,
            scales: {
                x: {
                    type: 'realtime',
                    realtime: {
                        duration: 20000,
                        refresh: 1000,
                        delay: 2000,
                        onRefresh: chart => {
                            chart.data.datasets.forEach(dataset => {
                                dataset.data.push({
                                    x: Date.now(),
                                    y: Math.random() * 100
                                });
                            });
                        }
                    }
                }
            }
        }
    });
}

// 初始化所有图表
document.addEventListener('DOMContentLoaded', () => {
    const currentChart = createChart(document.getElementById('currentChart').getContext('2d'), '电流');
    const voltageChart = createChart(document.getElementById('voltageChart').getContext('2d'), '电压');
    const speedChart = createChart(document.getElementById('speedChart').getContext('2d'), '转速');
    const powerChart = createChart(document.getElementById('powerChart').getContext('2d'), '功率');
});

