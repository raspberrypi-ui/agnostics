project ('agnostics','c')

share_dir = join_paths(get_option('prefix'), 'share')
bin_dir = join_paths(get_option('prefix'), 'bin')
resource_dir = join_paths(share_dir, meson.project_name())
ui_dir = join_paths(resource_dir, 'ui')
desktop_dir = join_paths(share_dir, 'applications')

i18n = import('i18n')

add_project_arguments('-DPACKAGE_LOCALE_DIR="' + share_dir + '/locale"', language : 'c' )
add_project_arguments('-DPACKAGE_UI_DIR="' + ui_dir + '"', language : [ 'c', 'cpp' ])

subdir('po')
subdir('src')
subdir('data')
