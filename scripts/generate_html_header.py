import os

def convert_html_to_cpp_string_literal(html_file_path, output_file_path, variable_name):
    with open(html_file_path, 'r') as html_file:
        html_content = html_file.read()

    cpp_string_literal = 'const char ' + variable_name + '[] PROGMEM = R"rawliteral(\n' + html_content + '\n)rawliteral";\n'

    upper_variable_name = variable_name.upper()

    with open(output_file_path, 'w') as output_file:
        output_file.write('#ifndef ' + upper_variable_name + '_H\n')
        output_file.write('#define ' + upper_variable_name + '_H\n\n')
        output_file.write('#include <Arduino.h>\n\n')
        output_file.write(cpp_string_literal)
        output_file.write('\n#endif // ' + upper_variable_name + '_H\n')

def generate_index(source, target, env):
    print("Generate index_html.h from index.html")
    html_file_path = 'data/index.html'
    output_file_path = 'lib/web_server/src/index_html.h'
    convert_html_to_cpp_string_literal(html_file_path, output_file_path, variable_name='index_html')

def generate_captive_portal(source, target, env):
    print("Generate captive_portal_html.h from captive_portal.html")
    html_file_path = 'data/captive_portal.html'
    output_file_path = 'lib/web_server/src/captive_portal_html.h'
    convert_html_to_cpp_string_literal(html_file_path, output_file_path, variable_name='captive_portal_html')

if __name__ == "__main__":
    html_file_path = 'data/index.html'
    output_file_path = 'lib/web_server/src/index_html.h'
    convert_html_to_cpp_string_literal(html_file_path, output_file_path, variable_name='index_html')
else:
    Import("env")
    generate_index(None, None, env)
    generate_captive_portal(None, None, env)
