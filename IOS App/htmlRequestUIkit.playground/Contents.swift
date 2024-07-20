import UIKit
//import Charts
import PlaygroundSupport
import MapKit

// Replace with your ThingSpeak Channel ID and API Key
let channelID = "2350211"
let readApiKey = "OJZXWYDNTDX78N91"


// Define the ThingSpeak API URL
let urlString = "https://api.thingspeak.com/channels/\(channelID)/feeds.json?api_key=\(readApiKey)"

// Example JSON with object root:
/*
    {
         "channel": {
             "id": 2350211,
             "name": "HomeSentry",
             "latitude": "45.777126435",
             "longitude": "3.0872824455",
             "field1": "Temperature1",
             "field2": "Pressure1",
             "created_at": "2023-11-19T11:01:01Z",
             "updated_at": "2023-12-02T20:57:37Z",
             "last_entry_id": 48
           },
         "feeds": [
           {
             "created_at": "2023-12-02T21:01:05Z",
             "entry_id": 1,
             "field1": "20.20000",
             "field2": null
           }],
    }
*/



var TimeStamp:[String] = []
var EntryID:[Int] = []
var Temperature:[Float] = []
var Pressure:[Float] = []


// Define the nested dictionary structure
struct ChannelDictionary: Decodable {
    let id: Int
    let name: String
    let latitude: String
    let longitude: String
    let field1: String
    let field2: String
    let created_at: String
    let updated_at: String
    let last_entry_id: Int
}

struct ItemData: Decodable {
    let created_at: String
    let entry_id: Int
    let field1: String?
    let field2: String?
}

// Define the structure of the JSON file to parse
struct ThingSpeakData: Decodable {
    let channel: ChannelDictionary
    let feeds: [ItemData]
}




// Perform the API request and fetch data
func fetchData() {
    guard let url = URL(string: urlString) else {
        print("Invalid URL")
        return
    }
//    let url = URL(string: urlString)!

    URLSession.shared.dataTask(with: url) { (data, response, error) in
        
        if let data = data {
            do {
                let decoder = JSONDecoder()
                
                let result = try decoder.decode(ThingSpeakData.self, from: data)
                
                for element in result.feeds {
                    // Print in console
//                    print("Temperature: \(element.field1) °C")
//                    print("Pressure: \(element.field1) Pa")
                    
                    // Add values to the corresponding arrays
//                    print(Float(element.field1 ?? "-1.0")!)
                    TimeStamp.append(element.created_at)
                    Temperature.append(Float(element.field1 ?? "-1.0")!)
                    Pressure.append(Float(element.field2 ?? "-1.0")!)
                    EntryID.append(element.entry_id)
                }
                
                Temperature.map() {$0}
                
            } catch {
                print("Error decoding JSON: \(error)")
            }
        }
    }.resume()
}

// Call the fetchData function
fetchData()



func convertTimeStamp(dateString:String) -> Date {
    let dateFormatter = DateFormatter()
    dateFormatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss'Z'"
    let date = dateFormatter.date(from: dateString)
    return date ?? dateFormatter.date(from: "2000-01-01T00:00:00Z")!
}

convertTimeStamp(dateString:"2023-12-18T13:15:53Z")
"2023-12-18T11:30:26Z".dropLast()+"+0000"

func convertStringToDate(dateString: String) -> Date? {
    let dateFormatter = DateFormatter()
    dateFormatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss'Z'"
    //dateFormatter.locale = Locale(identifier: "en_US_POSIX") // Set locale to ensure parsing consistency
    dateFormatter.timeZone = TimeZone(identifier: "Europe/Paris") // Use UTC timezone or your desired timezone

    if let date = dateFormatter.date(from: dateString) {
        return date
    } else {
        print("Invalid date format")
        return nil
    }
}

convertStringToDate(dateString: "2023-01-15T14:30:00Z")

Float("-1.0")


let date1 = convertTimeStamp(dateString:"2023-12-17T13:15:53Z")
let date2 = convertTimeStamp(dateString:"2023-11-16T13:15:53Z")




func haveSameDay(_ date1: Date, _ date2: Date) -> Bool {
    let calendar = Calendar.current

    // Extract date components
    let components1 = calendar.dateComponents([.year, .month, .day], from: date1)
    let components2 = calendar.dateComponents([.year, .month, .day], from: date2)

    // Compare date components
    return components1.year == components2.year && components1.month == components2.month && components1.day == components2.day
}



func haveSameWeek(_ date1: Date, _ date2: Date, calendar: Calendar = .current) -> Bool {
    let components1 = calendar.dateComponents([.yearForWeekOfYear, .weekOfYear], from: date1)
    let components2 = calendar.dateComponents([.yearForWeekOfYear, .weekOfYear], from: date2)

    return components1.yearForWeekOfYear == components2.yearForWeekOfYear &&
           components1.weekOfYear == components2.weekOfYear
}



func haveSameMonth(_ date1: Date, _ date2: Date) -> Bool {
    let calendar = Calendar.current

    // Extract date components
    let components1 = calendar.dateComponents([.year, .month, .day], from: date1)
    let components2 = calendar.dateComponents([.year, .month, .day], from: date2)

    // Compare date components
    return components1.year == components2.year && components1.month == components2.month
}



func haveSameYear(_ date1: Date, _ date2: Date) -> Bool {
    let calendar = Calendar.current

    // Extract date components
    let components1 = calendar.dateComponents([.year, .month, .day], from: date1)
    let components2 = calendar.dateComponents([.year, .month, .day], from: date2)

    // Compare date components
    return components1.year == components2.year
}


haveSameDay(date1, date2)
haveSameWeek(date1, date2)
haveSameMonth(date1, date2)
haveSameYear(date1, date2)



let dateArray = [date1, date2]

var dateBoolArray:[Bool] = []

for date in dateArray {
    //dateBoolArray.append(haveSameMonth(date, Date()))
    if haveSameMonth(date, Date()) {
        date
    }
}

//zip(array1, array2).compactMap { $0 == "true" ? $1 : nil }


Float("-1.1234")

var variable10 = 123
var index = 10

"variable\(index)"



1.1111

CLLocationDegrees("1.111")
