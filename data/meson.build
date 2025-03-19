install_data('agnostics.ui', install_dir: ui_dir)
install_data('sd_bench.fio', install_dir: resource_dir)
install_data('sdtest.sh', install_dir: resource_dir)

i18n.merge_file(input: 'agnostics.desktop.in',
  output: 'agnostics.desktop',
  type: 'desktop',
  po_dir: '../po',
  install: true,
  install_dir: desktop_dir
)
