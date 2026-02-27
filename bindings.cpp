#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "HumdrumFile.h"

#include <sstream>

namespace py = pybind11;

using hum::HumdrumFile;

PYBIND11_MODULE(pyhumlib, m) {

    py::class_<HumdrumFile>(m, "HumdrumFile")

        // Constructors
        .def(py::init<>())
        .def(py::init<const std::string&>())

        // Read from filename (disambiguated overload)
        .def("read",
             static_cast<bool (HumdrumFile::*)(const std::string&)>(
                 &HumdrumFile::read))

        // Read from Python string
        .def("read_string",
             [](HumdrumFile& self, const std::string& data) {
                 std::stringstream ss(data);
                 self.read(ss);
             })

        // Line count
        .def("get_line_count", &HumdrumFile::getLineCount)

        // Export as XML
        .def("to_xml",
             [](HumdrumFile& self,
                int level,
                const std::string& indent) {

                 std::stringstream ss;
                 self.printXml(ss, level, indent);
                 return ss.str();
             },
             py::arg("level") = 0,
             py::arg("indent") = "\t"
        );
}